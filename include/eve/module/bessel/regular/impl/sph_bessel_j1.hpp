//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/bessel/regular/sph_bessel_jn.hpp>

namespace eve::detail
{
  template<floating_value T>
  EVE_FORCEINLINE auto sph_bessel_j1_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    return  sph_bessel_jn(1u, x);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked cases
  template<conditional_expr C, typename ... Ts>
  EVE_FORCEINLINE auto
  sph_bessel_j1_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
  {
    return mask_op(cond, eve::sph_bessel_j1, ts ...);
  }

}
