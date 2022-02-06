//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/overload.hpp>
#include <type_traits>

namespace eve::detail
{
  template<integral_value T, integral_value U>
  EVE_FORCEINLINE auto shl_(EVE_SUPPORTS(cpu_), T a, U s) noexcept
  {
    if constexpr( scalar_value<T> && scalar_value<U> )  return  static_cast<T>(a << s);
    else if constexpr( scalar_value<T>)
    {
      using w_t = as_wide_t<T, cardinal_t<U>>;
      return w_t(a) << s;
    }
    else return a << s;
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, integral_value T, integral_value U>
  EVE_FORCEINLINE auto shl_(EVE_SUPPORTS(cpu_), C const &cond, T const &a, U const &b) noexcept
  {
    return mask_op(  cond, eve::shl, a, b);
  }

}
