//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/asin.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto asind_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return radindeg(eve::asin(a));
    else
      return apply_over(eve::asind, a);
  }

}
