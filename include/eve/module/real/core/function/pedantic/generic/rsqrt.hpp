//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/inf.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/is_denormal.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/traits.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T rsqrt_(EVE_SUPPORTS(cpu_), pedantic_type const &, T a0) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      return a0 ? rec(eve::sqrt(a0)) : inf(eve::as(a0));
    }
    else if constexpr( has_aggregated_abi_v<T> )
    {
      return aggregate(pedantic(eve::rsqrt), a0);
    }
    else
    {
      return map(pedantic(rsqrt), a0);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto rsqrt_(EVE_SUPPORTS(cpu_), C const &cond, pedantic_type const &, U const &t) noexcept
  {
    return mask_op( cond, pedantic(eve::rsqrt), t);
  }
}
