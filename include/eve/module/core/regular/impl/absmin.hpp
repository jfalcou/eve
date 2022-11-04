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
#include <eve/module/core/regular/min.hpp>
#include <eve/traits/common_compatible.hpp>

#include <type_traits>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(absmin, a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept requires has_native_abi_v<T>
{
  return eve::abs(eve::min(a, b));
}

//================================================================================================
// Masked case
//================================================================================================
template<decorator D, conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_), C const& cond, D const&, U const& t, V const& f) noexcept
requires(std::convertible_to<U, decltype(absmin(t, f))>)
{
  return mask_op(cond, D()(eve::absmin), t, f);
}

template<conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_),
        C const& cond,
        U const& t,
        V const& f) noexcept
requires(std::convertible_to<U, decltype(absmin(t, f))>)
{
  return mask_op(cond, eve::absmin, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
common_compatible_t<T0, T1, Ts...>
absmin_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
{
  return eve::abs(eve::min(a0, a1, args...));
}
//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
absmin_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return eve::abs(get<0>(tup));
  else return eve::abs(kumi::apply( [&](auto... m) { return min(m...); }, tup));
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
absmin_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return d(eve::abs)(get<0>(tup));
  else return d(eve::abs)(kumi::apply( [&](auto... m) { return d(min)(m...); }, tup));

}
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, value T0, value T1, value... Ts>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) noexcept
requires(std::convertible_to<T0, decltype(absmin(a0, a1, args...))>)
{
  return mask_op(cond, eve::absmin, a0, a1, args...);
}

}
