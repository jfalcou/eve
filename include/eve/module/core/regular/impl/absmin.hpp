//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/detail/function/conditional.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> decltype(eve::abs(eve::max(a, b)))
{
  return arithmetic_call(absmin, a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
-> decltype(eve::abs(a))
{
  if constexpr(has_native_abi_v<T>)
    return eve::abs(eve::min(a, b));
  else
    return apply_over(absmin, a, b);
}

//================================================================================================
// Masked case
//================================================================================================
template<decorator D, conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_), C const& cond, D const&, U const& t, V const& f) noexcept
-> decltype(absmin(t, f))
{
  return mask_op(cond, D()(eve::absmin), t, f);
}

template<conditional_expr C, ordered_value U, ordered_value V>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_),
        C const& cond,
        U const& t,
        V const& f) noexcept
-> decltype(absmin(t, f))
{
  return mask_op(cond, eve::absmin, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
absmin_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args) noexcept
-> decltype(eve::abs(eve::min(a0, a1, args...)))
{
  return eve::abs(eve::min(a0, a1, args...));
}
//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
absmin_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return eve::abs(get<0>(tup));
  else return eve::abs(kumi::apply( [&](auto... m) { return min(m...); }, tup));
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
absmin_(EVE_SUPPORTS(cpu_), D const & d, Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return d(eve::abs)(get<0>(tup));
  else return d(eve::abs)(kumi::apply( [&](auto... m) { return d(min)(m...); }, tup));

}
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, ordered_value T0, ordered_value T1, ordered_value... Ts>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args) noexcept
->decltype(absmin(a0, a1, args...))
{
  return mask_op(cond, eve::absmin, a0, a1, args...);
}

}
