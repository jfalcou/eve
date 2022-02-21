//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/inc.hpp>
#include <eve/module/core/regular/is_not_equal.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T inc_(EVE_SUPPORTS(cpu_)
                                  , saturated_type const &
                                  , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(integral_value<T>)
      {
        return inc[ a != valmax(eve::as(a)) ](a);
      }
      else if constexpr(floating_value<T>)
      {
        return inc(a);
      }
    }
    else
    {
      return apply_over(saturated(inc), a);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto inc_(EVE_SUPPORTS(cpu_), C const &cond
                           , saturated_type const &, U const &t) noexcept
  {
    return mask_op(  cond, saturated(eve::inc), t);
  }
}
