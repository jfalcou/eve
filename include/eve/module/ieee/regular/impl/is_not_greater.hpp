//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE  auto is_not_greater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(is_not_greater, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE  auto is_not_greater_(EVE_SUPPORTS(cpu_)
                            , T const &a
                            , T const &b) noexcept
  {
    if constexpr(integral_value<T>) return is_less_equal(a, b);
    else                            return is_less_equal(a, b) || is_unordered(a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto is_not_greater_(EVE_SUPPORTS(cpu_), C const &cond, U const &u, V const &v) noexcept
  {
    return logical_mask_op(cond, is_not_greater, u, v);
  }
}
