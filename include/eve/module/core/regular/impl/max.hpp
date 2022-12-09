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

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// Regular
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
max_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(max, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE T
max_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  if constexpr(scalar_value<T>)
    return b < a ? a : b;
  else
    return apply_over(max, a, b);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
max_(EVE_SUPPORTS(cpu_),
     C const& cond,
     U const& t,
     V const& f) noexcept
{
  return mask_op(cond, eve::max, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
max_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
-> common_value_t<T0, T1, Ts...>
{
  using r_t = common_value_t<T0, T1, Ts...>;
  r_t that(max(r_t(a0), r_t(a1)));
  ((that = max(that, r_t(args))), ...);
  return that;
}

template<decorator D,  ordered_value... Ts>
auto
max_(EVE_SUPPORTS(cpu_), D const &, Ts... args)
{
  return max(args...);
}

//================================================================================================
// N parameters masked
//================================================================================================
template<conditional_expr C, ordered_value T0, ordered_value T1, ordered_value... Ts>
auto max_(EVE_SUPPORTS(cpu_), C const & cond, T0 a0, T1 a1, Ts... args)
{
  return mask_op(cond, eve::max, a0, a1, args...);
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
max_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return max(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
max_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return d(max)(m...); }, tup);
}

//================================================================================================
// Predicate case
//================================================================================================
template<typename Callable>
EVE_FORCEINLINE auto
max_(EVE_SUPPORTS(cpu_), Callable f)
{
  if constexpr( std::same_as<Callable, callable_is_less_> ) return eve::max;
  else if constexpr( std::same_as<Callable, callable_is_greater_> ) return eve::min;
  else return [f](auto x, auto y) { return if_else(f(y, x), x, y); };
}

}
