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
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto lbeta_(EVE_SUPPORTS(cpu_)
                             , T a
                             , U b) noexcept
  -> decltype(arithmetic_call(lbeta, a, b))
  {
    return arithmetic_call(lbeta, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T lbeta_(EVE_SUPPORTS(cpu_), T a0,  T a1) noexcept
  requires(has_native_abi_v<T>)
  {
    auto y = a0+a1;
    return lgamma(a0)+lgamma(a1)-lgamma(y);
  }
}
