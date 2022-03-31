//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T>
  EVE_FORCEINLINE auto frac_(EVE_SUPPORTS(cpu_)
                            , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        if constexpr(scalar_value<T>)
        {
          if (!a) return a;
          else return a - trunc(a);
        }
        else
        {
          return if_else(is_eqz(a), a, a - trunc(a));
        }
      }
      else return zero(eve::as(a));
    }
    else return apply_over(frac, a);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, floating_real_value U>
  EVE_FORCEINLINE auto frac_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op( cond, eve::frac, t);
  }
}
