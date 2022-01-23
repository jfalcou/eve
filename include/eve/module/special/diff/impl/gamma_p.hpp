//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/gamma_p.hpp>
#include <eve/module/special/regular/lgamma.hpp>

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
