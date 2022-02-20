//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/one.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T m1to_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    if constexpr( has_native_abi_v<T> ) return one(eve::as<T>()) - v;
    else                                return apply_over(m1to, v);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto m1to_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::m1to, t);
  }
}
