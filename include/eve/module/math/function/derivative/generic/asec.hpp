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

#include <eve/function/derivative.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T asec_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , T const &x) noexcept
  {
    return -rec(eve::abs(x)*sqrt(dec(sqr(x))));
  }
}
