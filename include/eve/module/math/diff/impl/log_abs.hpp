//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log_abs_(EVE_SUPPORTS(cpu_)
                                     , diff_type<1> const &
                                     , T x) noexcept
  {
    return rec(x);
  }
}
