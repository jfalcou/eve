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

#include <eve/function/secpi.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/pi.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T tanpi_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , T const &x) noexcept
  {
    return pi(as(x))*sqr(secpi(x));
  }
}
