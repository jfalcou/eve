//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fnma.hpp>
#include <eve/concept/value.hpp>


namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE T refine_rec_(EVE_SUPPORTS(cpu_)
                               , T const &a0
                               , T const &x) noexcept
  {
    // Newton-Raphson: 1/X ~= (1-a0*x)*x + x
    return fma(fnma(x, a0, one(eve::as(a0))), x, x);
  }
}

