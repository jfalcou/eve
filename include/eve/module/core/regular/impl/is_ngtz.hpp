//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/zero.hpp>
#include <eve/module/core/regular/nan.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_greater.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_ngtz_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(unsigned_value<T>)           return is_eqz(a);
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        if constexpr(integral_value<T>)      return is_lez(a);
        else if constexpr(floating_value<T>) return is_lez(a) || is_nan(a);
      }
      else                                   return is_not_greater(a, zero(eve::as(a)));
    }
    else                                     return apply_over(is_ngtz, a);
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_ngtz_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return is_not_greater[cond](u, zero(as(u)));
  }
}
