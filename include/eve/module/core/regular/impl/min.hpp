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
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/max.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// Regular
template<real_value T, real_value U>
EVE_FORCEINLINE auto
min_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(min, a, b);
}

template<real_scalar_value T>
EVE_FORCEINLINE T
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
     V const& f) noexcept  -> common_value_t<V, U>
{
  return mask_op(cond, eve::min, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
auto
min_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args) noexcept
-> common_value_t<T0, T1, Ts...>
{
  using r_t = common_value_t<T0, T1, Ts...>;
  r_t that(min(r_t(a0), r_t(a1)));
  ((that = min(that, r_t(args))), ...);
  return that;
}

template<decorator D,  real_value... Ts>
auto
min_(EVE_SUPPORTS(cpu_), D const &, Ts... args)
{
  return min(args...);
}

//================================================================================================
// N parameters masked
//================================================================================================
template<conditional_expr C, real_value T0, real_value T1, real_value... Ts>
auto min_(EVE_SUPPORTS(cpu_), C const & cond, T0 a0, T1 a1, Ts... args) noexcept
{
  return mask_op(cond, eve::min, a0, a1, args...);
}
//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
min_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return min(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
min_(EVE_SUPPORTS(cpu_), D const & d, Ts tup) noexcept
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
