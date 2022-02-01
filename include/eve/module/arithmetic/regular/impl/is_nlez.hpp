//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_less_equal.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_nlez_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(unsigned_value<T>)       return is_nez(a);
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if constexpr(integral_value<T>)      return is_gtz(a);
        else if constexpr(floating_value<T>) return is_gtz(a) || is_nan(a);
      }
      else                                   return is_not_less_equal(a, zero(eve::as(a)));
    }
    else                                     return apply_over(is_nlez, a);
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_nlez_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return is_not_less_equal[cond](u, zero(as(u)));
  }
}
