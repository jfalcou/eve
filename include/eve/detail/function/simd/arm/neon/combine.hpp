//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(neon128_ const &, wide<T, N> const &l, wide<T, N> const &h) noexcept
    requires std::same_as<abi_t<T, N>, arm_64_>
  {
    using that_t = wide<T, typename N::combined_type>;

    if constexpr( N::value * sizeof(T) == eve::arm_64_::bytes )
    {
      if constexpr( std::is_same_v<T, float> )
      {
        return vcombine_f32(l, h);
      }
      else if constexpr( current_api >= asimd && std::is_same_v<T, double> )
      {
        return vcombine_f64(l, h);
      }
      else if constexpr( std::signed_integral<T> )
      {
        if constexpr( sizeof(T) == 8 )
        {
          return vcombine_s64(l, h);
        }
        if constexpr( sizeof(T) == 4 )
        {
          return vcombine_s32(l, h);
        }
        if constexpr( sizeof(T) == 2 )
        {
          return vcombine_s16(l, h);
        }
        if constexpr( sizeof(T) == 1 )
        {
          return vcombine_s8(l, h);
        }
      }
      else if constexpr( std::unsigned_integral<T> )
      {
        if constexpr( sizeof(T) == 4 )
        {
          return vcombine_u32(l, h);
        }
        if constexpr( sizeof(T) == 2 )
        {
          return vcombine_u16(l, h);
        }
        if constexpr( sizeof(T) == 8 )
        {
          return vcombine_u64(l, h);
        }
        if constexpr( sizeof(T) == 1 )
        {
          return vcombine_u8(l, h);
        }
      }
    }
    else
    {
      auto mask = [&](auto... I) {
        uint8x8_t m = {static_cast<std::uint8_t>(I)...,
                       static_cast<std::uint8_t>(I + eve::arm_64_::bytes)...};
        return m;
      };

      uint8x8x2_t lh   = {{(uint8x8_t)l.storage(), (uint8x8_t)h.storage()}};
      auto        that = vtbl2_u8(lh, apply<(sizeof(T) * N::value)>(mask));

      return that_t(typename that_t::storage_type(that));
    }
  }
}
