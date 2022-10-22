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
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// Regular
template<real_value T, real_value U>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(min, a, b);
}

template<real_scalar_value T>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  return b < a ? b : a;
}

template<real_simd_value T>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  return apply_over(min, a, b);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, real_value U, real_value V>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(cpu_),
     C const& cond,
     U const& t,
     V const& f) noexcept requires compatible_values<U, V>
{
  return mask_op(cond, eve::min, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
auto
min_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
{
  using r_t = common_compatible_t<T0, T1, Ts...>;
  r_t that(min(r_t(a0), r_t(a1)));
  ((that = min(that, r_t(args))), ...);
  return that;
}

//================================================================================================
// N parameters masked
//================================================================================================
template<conditional_expr C, real_value T0, real_value T1, real_value... Ts>
auto min_(EVE_SUPPORTS(cpu_), C const & cond, T0 a0, T1 a1, Ts... args)
{
  return mask_op(cond, eve::min, a0, a1, args...);
}
//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_tuple Ts>
auto
min_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return min(m...); }, tup);
}

template<decorator D, kumi::non_empty_tuple Ts>
auto
min_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return d(min)(m...); }, tup);
}

//================================================================================================
// Predicate case
//================================================================================================
template<typename Callable>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(cpu_), Callable f)
{
  if constexpr( std::same_as<Callable, callable_is_less_> ) return eve::min;
  else if constexpr( std::same_as<Callable, callable_is_greater_> ) return eve::max;
  else return [f](auto x, auto y) { return if_else(f(y, x), y, x); };
}

}
