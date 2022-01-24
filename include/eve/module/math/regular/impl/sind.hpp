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
#include <eve/module/math/regular/div_180.hpp>
#include <eve/module/math/regular/sinpi.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto sind_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return D()(sinpi)(div_180(a0));
    }
    else
      return apply_over(D()(sind), a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto sind_(EVE_SUPPORTS(cpu_), T const &a0) noexcept
  {
    return sind(regular_type(), a0);
  }

}
