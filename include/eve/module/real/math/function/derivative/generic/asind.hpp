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

#include <eve/function/derivative/asin.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/radindeg.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T asind_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , T const &x) noexcept
  {
    return  radindeg(derivative(asin)(x));
  }
}
