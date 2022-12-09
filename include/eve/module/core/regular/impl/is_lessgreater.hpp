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
#include <eve/module/core/regular/is_not_equal.hpp>
#include <eve/module/core/regular/is_ordered.hpp>
#include <eve/module/core/regular/logical_and.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
is_lessgreater_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_logical_t<T, U>
{
  return arithmetic_call(is_lessgreater, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
is_lessgreater_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  return (is_not_equal(a, b) && is_ordered(a, b));
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
is_lessgreater_(EVE_SUPPORTS(cpu_), C const& cond, U const& u, V const& v) noexcept
{
  return logical_mask_op(cond, is_lessgreater, u, v);
}
}
