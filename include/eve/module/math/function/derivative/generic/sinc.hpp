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

#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sinc_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , T const &x) noexcept
  {
    [s, c] = sincos(x);
    return if_else(is_eqz(x), zero, fma(x, c, s)/sqr(x));
  }
}
