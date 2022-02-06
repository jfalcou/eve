//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/zero.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T nearest_(EVE_SUPPORTS(cpu_)
                                      , diff_type<1> const &
                                      , T x) noexcept
  {
    return zero(as(x));
  }
}
