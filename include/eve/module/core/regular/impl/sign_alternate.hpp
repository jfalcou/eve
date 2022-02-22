//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/is_odd.hpp>
#include <eve/module/core/regular/is_flint.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<signed_value T>
  EVE_FORCEINLINE constexpr auto sign_alternate_(EVE_SUPPORTS(cpu_), T const &n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)),  "sign_alternate : some entries are not flint");
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr(floating_value<T>)
        return if_else(is_not_finite(n), allbits, if_else(is_odd(n), mone, one(as(n))));
      else
        return if_else(is_odd(n), mone, one(as(n)));
    }
    else
      return apply_over(sign_alternate, n);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, signed_value U>
  EVE_FORCEINLINE auto sign_alternate_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return mask_op(  cond, eve::sign_alternate, t);
  }
}
