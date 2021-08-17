//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/frac.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_not_flint_(EVE_SUPPORTS(cpu_)
                                          , pedantic_type const &
                                          , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>) return true_(eve::as<T>());
      if constexpr(floating_value<T>) return is_nez(frac(a)) || (a > eve::maxflint(eve::as<T>()));
    }
    else                              return apply_over(pedantic(is_not_flint), a);
  }
}
