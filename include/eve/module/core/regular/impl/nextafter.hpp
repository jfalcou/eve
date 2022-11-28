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
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/prev.hpp>

#include <concepts>

#include <type_traits>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE constexpr auto
nextafter_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(nextafter, a, b);
}

template<real_value T>
EVE_FORCEINLINE constexpr auto
nextafter_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
requires has_native_abi_v<T>
{
  if constexpr( scalar_value<T> )
    return (a < b) ? next(a) : ((b < a) ? prev(a) : a);
  else if constexpr( simd_value<T> )
    return if_else(a < b, next(a), if_else(b < a, prev(a), a));
}
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, real_value T, real_value U>
EVE_FORCEINLINE auto
nextafter_(EVE_SUPPORTS(cpu_), C const& cond
          , T const& x, U const& y) noexcept
-> decltype(nextafter(x, y))
{
  return mask_op(cond, eve::nextafter, x, y);
}
}
