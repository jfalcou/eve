//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/is_greater.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/module/arithmetic/constant/sqrtvalmax.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr auto sqr_(EVE_SUPPORTS(cpu_)
                                  , saturated_type const &
                                  , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        return sqr(a0);
      }
      else if constexpr(scalar_value<T>)
      {
        return (eve::saturated(eve::abs)(a0) > sqrtvalmax(eve::as(a0))) ? valmax(eve::as(a0)) : sqr(a0);
      }
      else
      {
        return if_else((saturated(abs)(a0) > sqrtvalmax(eve::as(a0))), valmax(eve::as(a0)), sqr(a0));
      }
    }
    else
    {
      return apply_over(saturated(sqr), a0);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto sqr_(EVE_SUPPORTS(cpu_), C const &cond, saturated_type const &
                           , U const &t) noexcept
  {
    return mask_op( cond, saturated(eve::sqr), t);
  }
}
