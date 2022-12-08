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
#include <eve/module/core/constant/false.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE constexpr auto
is_unordered_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_logical_t<T, U>
{
  return arithmetic_call(is_unordered, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE constexpr as_logical_t<T>
is_unordered_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    if constexpr( integral_value<T> ) return false_(eve::as(a));
    else return (a != a) || (b != b);
  }
  else return apply_over(is_unordered, a, b);
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
is_unordered_(EVE_SUPPORTS(cpu_), C const& cond, U const& u, V const& v) noexcept
{
  return logical_mask_op(cond, is_unordered, u, v);
}
}
