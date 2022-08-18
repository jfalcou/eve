//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/traits/common_compatible.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(absmax, a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept requires has_native_abi_v<T>
{
  return eve::abs(eve::max(a, b));
}

//================================================================================================
// Masked case
//================================================================================================
template<decorator D, conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), C const& cond, D const&, U const& t, V const& f) noexcept
requires(std::convertible_to<U, decltype(absmax(t, f))>)
{
  return mask_op(cond, D()(eve::absmax), t, f);
}

template<conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_),
        C const& cond,
        U const& t,
        V const& f) noexcept
requires(std::convertible_to<U, decltype(absmax(t, f))>)
{
  return mask_op(cond, eve::absmax, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
common_compatible_t<T0, T1, Ts...>
absmax_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
{
  return eve::abs(eve::max(a0, a1, args...));
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value T0, value T1, value... Ts>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) noexcept
requires(std::convertible_to<T0, decltype(absmax(a0, a1, args...))>)
{
  return mask_op(cond, eve::absmax, a0, a1, args...);
}

}
