//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once


namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x) noexcept
  {

    return zero(as(x));
  }
}
