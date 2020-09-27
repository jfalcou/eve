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
#include <eve/function/gammaln.hpp>
#include <eve/function/signgam.hpp>
#include <eve/function/exp.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T beta_(EVE_SUPPORTS(cpu_), T a0,  T a1) noexcept
  {
    auto y = a0+a1;
    auto sign = signgam(a0)*signgam(a1)*signgam(y);
    return sign*exp(gammaln(a0)+gammaln(a1)-gammaln(y));
  }
}
