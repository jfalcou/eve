//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/zero.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr as_logical_t<T> is_lez_(EVE_SUPPORTS(cpu_)
                                                   , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(unsigned_value<T>) return is_eqz(a);
      else                            return a <= zero(eve::as(a));
    }
    else                              return apply_over(is_lez, a);
  }

  // -----------------------------------------------------------------------------------------------
  // logical masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto is_lez_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
  {
    return is_less_equal[cond](u, zero(as(u)));
  }
}
