//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/zero.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/logical_not.hpp>
#include <eve/module/core/regular/is_equal.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_eqz_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T> || is_logical_v<T>) return !a;
      else                                             return (a == zero(eve::as(a)));
    }
    else                                               return apply_over(is_eqz, a);
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_eqz_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return is_equal[cond](u, zero(as(u)));
  }
}
