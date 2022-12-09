//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/sign.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
negate_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(negate, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE T
negate_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  if constexpr(has_native_abi_v<T>)
  {
    if constexpr( signed_value<T> )
      return a * sign(b);
    else
      return if_else(is_nez(b), a, eve::zero);
  }
  else return apply_over(negate, a, b);
}
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
negate_(EVE_SUPPORTS(cpu_), C const& cond, T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return mask_op(cond, eve::negate, a, b);
}
}
