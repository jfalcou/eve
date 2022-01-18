//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math/regular/exp2.hpp>
#include <eve/constant/log_2.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T exp2_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x) noexcept
  {
    return exp2(x)*log_2(as(x));
  }
}
