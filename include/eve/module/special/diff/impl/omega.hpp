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
#include <eve/module/special/regular/omega.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto omega_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto omx = omega(x);
      return if_else(is_infinite(x), zero, omx/inc(omx));
    }
    else
      return apply_over(diff(omega), x);
  }
}
