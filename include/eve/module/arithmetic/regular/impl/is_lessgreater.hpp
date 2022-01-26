//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/is_not_equal.hpp>
#include <eve/module/arithmetic/regular/is_ordered.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto is_lessgreater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  //  requires compatible_values<T, U>
  {
    return arithmetic_call(is_lessgreater, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  auto is_lessgreater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  //  requires has_native_abi_v<T>
  {
    return  (is_not_equal(a, b) && is_ordered(a, b));
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto is_lessgreater_(EVE_SUPPORTS(cpu_), C const &cond, U const &u, V const &v) noexcept
  {
    return logical_mask_op(cond, is_lessgreater, u, v);
  }
}
