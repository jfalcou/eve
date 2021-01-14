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

#include <eve/constant/zero.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T nearest_(EVE_SUPPORTS(cpu_)
                                      , diff_type<1> const &
                                      , T x) noexcept
  {
    return zero(as(x));
  }
}
