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
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/logical_or.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
is_not_less_equal_(EVE_SUPPORTS(cpu_),
                   T const& a,
                   U const& b) noexcept
-> common_logical_t<T, U>
{
  return arithmetic_call(is_not_less_equal, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
is_not_less_equal_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  if constexpr( integral_value<T> ) return is_greater(a, b);
  else return is_greater(a, b) || is_unordered(a, b);
}

// -----------------------------------------------------------------------------------------------
// logical masked case
template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
is_not_less_equal_(EVE_SUPPORTS(cpu_), C const& cond, U const& u, V const& v) noexcept
{
  return logical_mask_op(cond, is_not_less_equal, u, v);
}
}
