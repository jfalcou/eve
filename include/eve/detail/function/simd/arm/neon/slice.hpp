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

#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>

#include <cstddef>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, arm_128_> const &a, Slice const &) noexcept
      requires(N::value > 1)
  {
    using type = wide<T, typename N::split_type>;

    if constexpr( Slice::value )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        return type {vget_high_f32(a)};
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        return type {vget_high_f64(a)};
      }
#endif
      else if constexpr( std::signed_integral<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          return type {vget_high_s64(a)};
        }
        if constexpr( sizeof(T) == 4 )
        {
          return type {vget_high_s32(a)};
        }
        if constexpr( sizeof(T) == 2 )
        {
          return type {vget_high_s16(a)};
        }
        if constexpr( sizeof(T) == 1 )
        {
          return type {vget_high_s8(a)};
        }
      }
      else
      {
        if constexpr( sizeof(T) == 8 )
        {
          return type {vget_high_u64(a)};
        }
        if constexpr( sizeof(T) == 4 )
        {
          return type {vget_high_u32(a)};
        }
        if constexpr( sizeof(T) == 2 )
        {
          return type {vget_high_u16(a)};
        }
        if constexpr( sizeof(T) == 1 )
        {
          return type {vget_high_u8(a)};
        }
      }
    }
    else
    {
      if constexpr( std::is_same_v<T, float> )
      {
        return type {vget_low_f32(a)};
      }
#if defined(__aarch64__)
      else if constexpr( std::is_same_v<T, double> )
      {
        return type {vget_low_f64(a)};
      }
#endif
      else if constexpr( std::signed_integral<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          return type {vget_low_s64(a)};
        }
        if constexpr( sizeof(T) == 4 )
        {
          return type {vget_low_s32(a)};
        }
        if constexpr( sizeof(T) == 2 )
        {
          return type {vget_low_s16(a)};
        }
        if constexpr( sizeof(T) == 1 )
        {
          return type {vget_low_s8(a)};
        }
      }
      else
      {
        if constexpr( sizeof(T) == 8 )
        {
          return type {vget_low_u64(a)};
        }
        if constexpr( sizeof(T) == 4 )
        {
          return type {vget_low_u32(a)};
        }
        if constexpr( sizeof(T) == 2 )
        {
          return type {vget_low_u16(a)};
        }
        if constexpr( sizeof(T) == 1 )
        {
          return type {vget_low_u8(a)};
        }
      }
    }
  }

  template<typename T, typename N, typename Slice>
  EVE_FORCEINLINE auto slice(wide<T, N, arm_64_> const &a, Slice const &) noexcept
      requires(N::value > 1)
  {
    using type = wide<T, typename N::split_type>;
    if constexpr( Slice::value )
    {
      auto select = [](auto const &v, auto size) {
        auto mask = [&](auto... I) {
          auto      offset = (sizeof(T) * size) / 2;
          uint8x8_t m      = {static_cast<std::uint8_t>(offset + I % offset)...};
          return m;
        };

        return vtbl1_u8((uint8x8_t)(v.storage()), apply<8>(mask));
      };

      return type((typename type::storage_type)(select(a, N {})));
    }
    else
    {
      return type(a.storage());
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N, arm_128_> const &a) noexcept requires(N::value > 1)
  {
    std::array<wide<T, typename N::split_type>, 2> that {slice(a, lower_), slice(a, upper_)};
    return that;
  }

  template<typename T, typename N>
  EVE_FORCEINLINE auto slice(wide<T, N, arm_64_> const &a) noexcept requires(N::value > 1)
  {
    std::array<wide<T, typename N::split_type>, 2> that {slice(a, lower_), slice(a, upper_)};
    return that;
  }
}

