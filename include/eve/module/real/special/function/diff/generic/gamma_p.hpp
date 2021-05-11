//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/gamma_p.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/log.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/derivative.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T gamma_p_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x
                                  , T const &k) noexcept
  {
    return exp(dec(k) * log(x) - x - lgamma(k));
  }
}
