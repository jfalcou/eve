//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>

#include <cstddef>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename Slice, arm_abi ABI>
  EVE_FORCEINLINE auto slice(neon128_ const&, wide<T, N, ABI> const &a, Slice const &) noexcept
      requires(N::value > 1)
  {
    using type = wide<T, typename N::split_type>;
    constexpr auto c = categorize<wide<T, N, ABI>>();

    if constexpr( Slice::value )
    {
            if constexpr( c == category::float32x4 )  return type{vget_high_f32(a)};
#if defined(__aarch64__)
      else  if constexpr( c == category::float64x2 )  return type{vget_high_f64(a)};
#endif
      else  if constexpr( c == category::int32x4  )   return type{vget_high_s32(a)};
      else  if constexpr( c == category::int64x2  )   return type{vget_high_s64(a)};
      else  if constexpr( c == category::int16x8  )   return type{vget_high_s16(a)};
      else  if constexpr( c == category::int8x16  )   return type{vget_high_s8(a) };
      else  if constexpr( c == category::uint64x2 )   return type{vget_high_u64(a)};
      else  if constexpr( c == category::uint32x4 )   return type{vget_high_u32(a)};
      else  if constexpr( c == category::uint16x8 )   return type{vget_high_u16(a)};
      else  if constexpr( c == category::uint8x16 )   return type{vget_high_u8(a) };
      else
      {
        auto select = [](auto const &v, auto size)
        {
          auto mask = [&](auto... I)
          {
            auto      offset = (sizeof(T) * size) / 2;
            uint8x8_t m      = {static_cast<std::uint8_t>(offset + I % offset)...};
            return m;
          };

          return vtbl1_u8((uint8x8_t)(v.storage()), apply<8>(mask));
      };

        return type((typename type::storage_type)(select(a, N {})));
      }
    }
    else
    {
            if constexpr( c == category::float32x4 )  return type{vget_low_f32(a)};
#if defined(__aarch64__)
      else  if constexpr( c == category::float64x2 )  return type{vget_low_f64(a)};
#endif
      else  if constexpr( c == category::int64x2  )   return type{vget_low_s64(a)};
      else  if constexpr( c == category::int32x4  )   return type{vget_low_s32(a)};
      else  if constexpr( c == category::int16x8  )   return type{vget_low_s16(a)};
      else  if constexpr( c == category::int8x16  )   return type{vget_low_s8(a) };
      else  if constexpr( c == category::uint64x2 )   return type{vget_low_u64(a)};
      else  if constexpr( c == category::uint32x4 )   return type{vget_low_u32(a)};
      else  if constexpr( c == category::uint16x8 )   return type{vget_low_u16(a)};
      else  if constexpr( c == category::uint8x16 )   return type{vget_low_u8(a) };
      else                                            return type(a.storage());
    }
  }

  template<typename T, typename N, arm_abi ABI>
  EVE_FORCEINLINE auto slice(neon128_ const&, wide<T, N, ABI> const &a) noexcept requires(N::value > 1)
  {
    std::array<wide<T, typename N::split_type>, 2> that { slice(neon128_{},a, lower_)
                                                        , slice(neon128_{},a, upper_)
                                                        };
    return that;
  }
}
