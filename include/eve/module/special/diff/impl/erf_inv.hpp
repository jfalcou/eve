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
#include <eve/module/math.hpp>
#include <eve/module/special/regular/erf_inv.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T erf_inv_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto sqrt_pi_2 = T(0.886226925452758013649);
      return sqrt_pi_2*exp(sqr(erf_inv(x)));
    }
    else
      return apply_over(diff(erf_inv), x);
  }
}
