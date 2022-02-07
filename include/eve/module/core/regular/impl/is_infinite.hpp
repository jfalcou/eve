//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/constant/false.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_infinite_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
          if constexpr(integral_value<T>)   return false_(eve::as(a));
    else  if constexpr(has_native_abi_v<T>) return (eve::abs(a) == inf(eve::as(a)));
    else                                    return apply_over(is_infinite, a);
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_infinite_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return logical_mask_op(cond, is_infinite, u);
  }
}
