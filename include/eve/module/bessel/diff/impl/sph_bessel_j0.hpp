//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_j0_(EVE_SUPPORTS(cpu_)
                                            , diff_type<1> const &
                                            , T const &x) noexcept
  {
    return diff(sinc)(x);
  }
}
