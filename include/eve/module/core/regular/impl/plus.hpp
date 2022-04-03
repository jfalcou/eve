//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/module/core/regular/add.hpp>

namespace eve::detail
{
  template<value T> EVE_FORCEINLINE auto plus_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return a;
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto plus_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return a+b;
  }

  //================================================================================================
  // Masked case
  //================================================================================================
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto plus_(EVE_SUPPORTS(cpu_), C const &, U const &t) noexcept
  {
    return t;
  }

  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto plus_(EVE_SUPPORTS(cpu_), C const &cond, U const &t, V const &f) noexcept
      requires compatible_values<U, V>
  {
    auto addit = [](auto x, auto y){return x+y;};
    return mask_op(  cond, addit, t, f);
  }
}
