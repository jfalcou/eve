//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/signgam.hpp>
#include <eve/function/exp.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<floating_real_value T,  floating_real_value U>
  EVE_FORCEINLINE common_compatible_t<T, U> beta_(EVE_SUPPORTS(cpu_), T a0,  U a1) noexcept
  {
    return arithmetic_call(beta, a0, a1);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T beta_(EVE_SUPPORTS(cpu_), T a0,  T a1) noexcept
  {
    auto y = a0+a1;
    auto sign = signgam(a0)*signgam(a1)*signgam(y);
    return sign*exp(lgamma(a0)+lgamma(a1)-lgamma(y));
  }
}
