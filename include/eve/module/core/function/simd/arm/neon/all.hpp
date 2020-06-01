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

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_), logical<wide<T, N, neon64_>> const &v0) noexcept
  {
    auto m = v0.bits();

    if constexpr( N::value == 1 )
    {
      return static_cast<bool>(m[0]);
    }
    else if constexpr( sizeof(T) == 4 )
    {
      m = vand_u32(m, vrev64_u32(m));
      return static_cast<bool>(m[0]);
    }
    else if constexpr( sizeof(T) == 2 )
    {
      if constexpr( N::value == 4 )
      {
        m = vand_u16(m, vrev64_u16(m));
      }
      m = vand_u16(m, vrev32_u16(m));
      return static_cast<bool>(m[0]);
    }
    else // if constexpr( sizeof(T) == 1 )
    {
      if constexpr( N::value == 8 )
      {
        m = vand_u8(m, vrev64_u8(m));
      }
      if constexpr( N::value >= 4 )
      {
        m = vand_u8(m, vrev32_u8(m));
      }

      m = vand_u8(m, vrev16_u8(m));
      return static_cast<bool>(m[0]);
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(neon128_),
                            logical<wide<T, N, neon128_>> const &v0) noexcept
  {
    auto [l, h] = v0.mask().slice();
    return all(l) && all(h);
  }
}

