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

#include <eve/function/acoth.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/log.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/inc.hpp>
#include <eve/constant/oneminus.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T acoth_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , T const &x) noexcept
  {
    return half(as(x))*log(inc(x)/oneminus(x));
  }
}
