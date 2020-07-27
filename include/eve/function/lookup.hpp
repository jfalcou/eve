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

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/lookup.hpp>

namespace eve::detail
{
  template<real_scalar_value T, integral_value I>
  EVE_FORCEINLINE constexpr T lookup_(EVE_SUPPORTS(cpu_), T const &a, I const &i)
  {
    return (i == static_cast<I>(-1)) ? 0 : a;
  }
}
