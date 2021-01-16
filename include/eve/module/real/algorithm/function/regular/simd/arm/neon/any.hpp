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
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(neon128_), logical<wide<T,N,arm_64_>> const &v0) noexcept
  {
    auto m = v0.bits();

    if constexpr( N::value == 1 )
    {
      return static_cast<bool>(m[0]);
    }
    else
    {
      m = vorr_u32(m, vrev64_u32(m));
      return static_cast<bool>(m[0]);
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(neon128_), logical<wide<T,N,arm_128_>> const &v0) noexcept
  {
    auto[l,h] = v0.mask().slice();
    return any(l) || any(h);
  }
}
