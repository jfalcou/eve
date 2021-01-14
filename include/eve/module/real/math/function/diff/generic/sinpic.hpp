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
#include <eve/function/sinpicospi.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/pi.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sinpic_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    auto [s, c] = sinpicospi(x);
    return if_else(is_eqz(x), zero, fms(x*pi(as(x)), c, s)/(pi(as(x))*sqr(x)));
  }
}
