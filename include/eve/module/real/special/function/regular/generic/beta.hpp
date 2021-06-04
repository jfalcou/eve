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

namespace eve::detail
{
  template<floating_value U, floating_value V>
  EVE_FORCEINLINE  auto betainc_(EVE_SUPPORTS(cpu_)
                              , U a
                              , V b ) noexcept
  -> decltype(arithmetic_call(beta, a, b))
  {
    return arithmetic_call(beta, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T beta_(EVE_SUPPORTS(cpu_), T a0,  T a1) noexcept
  requires(has_native_abi_v<T>)
  {
    auto y = a0+a1;
    auto sign = signgam(a0)*signgam(a1)*signgam(y);
    return sign*exp(lgamma(a0)+lgamma(a1)-lgamma(y));
  }
}
