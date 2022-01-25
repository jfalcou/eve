//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/regular/asin.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto asinpi_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return radinpi(eve::asin(a));
    else
      return apply_over(eve::asinpi, a);
  }

}
