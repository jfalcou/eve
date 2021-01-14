//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//=lo=================================================================================================
#pragma once

#include <eve/function/cscd.hpp>
#include <eve/function/cotd.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/deginrad.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T cscd_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return -deginrad(cscd(x)*cotd(x));
  }
}
