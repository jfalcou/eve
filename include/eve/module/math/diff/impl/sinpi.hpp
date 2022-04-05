//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/cospi.hpp>
#include <eve/module/math/constant/pi.hpp>


namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sinpi_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return pi(as(x))*cospi(x);
  }
}
