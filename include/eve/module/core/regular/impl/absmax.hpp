//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> decltype(eve::abs(eve::max(a, b)))
{
  return arithmetic_call(absmax, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
-> decltype(eve::abs(a))
{
  if constexpr(has_native_abi_v<T>)
    return eve::abs(eve::max(a, b));
  else
    return apply_over(absmax, a, b);
}

//================================================================================================
// Masked case
//================================================================================================
template<decorator D, conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), C const& cond, D const&, U const& t, V const& f) noexcept
-> decltype(absmax(t, f))
{
  return mask_op(cond, D()(eve::absmax), t, f);
}

template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_),
        C const& cond,
        U const& t,
        V const& f) noexcept
-> decltype(absmax(t, f))
{
  return mask_op(cond, eve::absmax, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
absmax_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args) noexcept
-> decltype(eve::abs(eve::max(a0, a1, args...)))
{
  return eve::abs(eve::max(a0, a1, args...));
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
absmax_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return eve::abs(get<0>(tup));
  else return eve::abs(kumi::apply( [&](auto... m) { return max(m...); }, tup));
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
absmax_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return d(eve::abs)(get<0>(tup));
  else return d(eve::abs)(kumi::apply( [&](auto... m) { return d(max)(m...); }, tup));
}


// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value T0, ordered_value T1, ordered_value... Ts>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(absmax(a0, a1, args...))
{
  return mask_op(cond, eve::absmax, a0, a1, args...);
}

}
