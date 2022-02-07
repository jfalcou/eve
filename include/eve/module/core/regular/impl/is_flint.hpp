//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/frac.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/module/core/constant/true.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto is_flint_(EVE_SUPPORTS(cpu_)
                                          , T const &a) noexcept
  {
    if constexpr(integral_value<T>)        return true_(eve::as<T>());
    else if constexpr(has_native_abi_v<T>) return is_eqz(frac(a));
    else                                   return apply_over(is_flint, a);
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_flint_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return logical_mask_op(cond, is_flint, u);
  }
}
