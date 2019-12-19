//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ANY_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_ARM_NEON_ANY_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <iostream>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(neon128_), logical<wide<T,N,neon64_>> const &v0) noexcept
  {
    auto m = v0.bits();

    if constexpr( N::value == 1 )
    {
      return static_cast<bool>(m[0]);
    }
    else if constexpr( sizeof(T) == 4 )
    {
      m = vorr_u32(m, vrev64_u32(m));
      return static_cast<bool>(m[0]);
    }
    else if constexpr( sizeof(T) == 2 )
    {
      if constexpr( N::value == 4) m = vorr_u16(m, vrev64_u16(m));
      m = vorr_u16(m, vrev32_u16(m));
      return static_cast<bool>(m[0]);
    }
    else //if constexpr( sizeof(T) == 1 )
    {
      if constexpr( N::value == 8)  m = vorr_u8(m, vrev64_u8(m));
      if constexpr( N::value >= 4)  m = vorr_u8(m, vrev32_u8(m));
      m = vorr_u8(m, vrev16_u8(m));
      return static_cast<bool>(m[0]);
    }
  }

  template<typename T, typename N>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(neon128_), logical<wide<T,N,neon128_>> const &v0) noexcept
  {
    auto[l,h] = v0.mask().slice();
    return any(l) || any(h);
  }
}

#endif
