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
#include <eve/module/math/regular/asinh.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto acsch_(EVE_SUPPORTS(cpu_), T const &x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      return asinh(rec(x));
    }
    else
    {
      return apply_over(acsch, x);
    }
  }
}
