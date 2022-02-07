//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/all.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_not_equal.hpp>
#include <eve/module/core/regular/logical_and.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/compatible.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE constexpr auto is_unordered_(EVE_SUPPORTS(cpu_)
                                              , T const &a
                                              , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(is_unordered, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_unordered_(EVE_SUPPORTS(cpu_)
                                                         , T const &a
                                                         , T const &b) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>) return false_(eve::as(a));
      else                            return (a != a) || (b != b);
    }
    else                              return apply_over(is_unordered, a, b);
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U, real_value V>
  EVE_FORCEINLINE auto is_unordered_(EVE_SUPPORTS(cpu_), C const &cond, U const &u, V const &v) noexcept
  {
    return logical_mask_op(cond, is_unordered, u, v);
  }
}
