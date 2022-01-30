//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/is_eqz.hpp>
#include <eve/module/arithmetic/regular/frac.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_flint_(EVE_SUPPORTS(cpu_)
                                          , pedantic_type const &
                                          , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>) return false_(eve::as<T>());
      if constexpr(floating_value<T>) return is_eqz(frac(a)) && (a <= eve::maxflint(eve::as<T>()));
    }
    else                              return apply_over(pedantic(is_flint), a);
  }
}
