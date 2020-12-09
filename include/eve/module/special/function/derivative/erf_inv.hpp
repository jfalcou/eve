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

#include <eve/function/erf_inv.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T erf_inv_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , T const &x) noexcept
  {
    auto sqrt_pi_2 = T(0.886226925452758013649); 
    return sqrt_pi_2*exp(sqr(erf_inv(oneminus(x)))); 
  }
}
