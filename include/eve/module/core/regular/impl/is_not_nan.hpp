//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/true.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_not_nan_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( integral_value<T> ) return true_(eve::as(a));
    else return a == a;
  }
  else return apply_over(is_not_nan, a);
}
// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, ordered_value U>
EVE_FORCEINLINE auto
is_not_nan_(EVE_SUPPORTS(cpu_), C const& cond, U const& u) noexcept
{
  return logical_mask_op(cond, is_not_nan, u);
}
}
