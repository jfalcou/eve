//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N> const &a, Slice const &) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    using type = wide<T, typename N::split_type>;
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( Slice::value )
    {
      if constexpr( c == category::float32x4 )  return type{vget_high_f32(a)};
      else  if constexpr( c == category::int32x4  )   return type{vget_high_s32(a)};
      else  if constexpr( c == category::int64x2  )   return type{vget_high_s64(a)};
      else  if constexpr( c == category::int16x8  )   return type{vget_high_s16(a)};
      else  if constexpr( c == category::int8x16  )   return type{vget_high_s8(a) };
      else  if constexpr( c == category::uint64x2 )   return type{vget_high_u64(a)};
      else  if constexpr( c == category::uint32x4 )   return type{vget_high_u32(a)};
      else  if constexpr( c == category::uint16x8 )   return type{vget_high_u16(a)};
      else  if constexpr( c == category::uint8x16 )   return type{vget_high_u8(a) };
      else if constexpr( current_api >= asimd && c == category::float64x2 )  return type{vget_high_f64(a)};
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
      else  if constexpr( c == category::int64x2  )   return type{vget_low_s64(a)};
      else  if constexpr( c == category::int32x4  )   return type{vget_low_s32(a)};
      else  if constexpr( c == category::int16x8  )   return type{vget_low_s16(a)};
      else  if constexpr( c == category::int8x16  )   return type{vget_low_s8(a) };
      else  if constexpr( c == category::uint64x2 )   return type{vget_low_u64(a)};
      else  if constexpr( c == category::uint32x4 )   return type{vget_low_u32(a)};
      else  if constexpr( c == category::uint16x8 )   return type{vget_low_u16(a)};
      else  if constexpr( c == category::uint8x16 )   return type{vget_low_u8(a) };
      else if constexpr( current_api >= asimd &&  c == category::float64x2 )  return type{vget_low_f64(a)};
      else                                            return type(a.storage());
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N> const &a) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    std::array<wide<T, typename N::split_type>, 2> that{ slice(a, lower_), slice(a, upper_) };
    return that;
  }
}
