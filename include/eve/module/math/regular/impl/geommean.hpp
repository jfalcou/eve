//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/pow_abs.hpp>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U>
EVE_FORCEINLINE auto
geommean_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(geommean, a, b);
}

template<floating_real_value T>
EVE_FORCEINLINE T
geommean_(EVE_SUPPORTS(cpu_), T a, T b) noexcept requires has_native_abi_v<T>
{
  return if_else(is_nltz(sign(a) * sign(b)), sqrt(abs(a)) * sqrt(abs(b)), allbits);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, floating_real_value U, floating_real_value V>
EVE_FORCEINLINE auto
geommean_(EVE_SUPPORTS(cpu_),
          C const& cond,
          U const& t,
          V const& f) noexcept 
-> decltype( if_else(cond, geommean(t, f), t) )
{
  return mask_op(cond, eve::geommean, t, f);
}

//================================================================================================
// N parameters
//================================================================================================

template<floating_real_value T0, floating_real_value T1, floating_real_value... Ts>
auto
geommean_(EVE_SUPPORTS(cpu_),
          T0 a0,
          T1 a1,
          Ts... args)
  -> common_value_t<T0, T1, Ts...>
{
  using r_t   = common_value_t<T0, T1, Ts...>;
  using elt_t = element_type_t<r_t>;
  elt_t invn  = rec(elt_t(sizeof...(args) + 2u));
  r_t   that(pow_abs(r_t(a0), invn) * pow_abs(r_t(a1), invn));
  r_t   sgn  = sign(r_t(a0)) * sign(r_t(a1));
  auto  next = [&](auto avg, auto x)
  {
    sgn *= sign(x);
    return avg * pow_abs(r_t(x), invn);
  };
  ((that = next(that, args)), ...);
  return if_else(is_even(sizeof...(args)) && is_ltz(sgn), eve::allbits, sgn * that);
}


//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
geommean_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return geommean(m...); }, tup);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, floating_value T0, floating_value T1, floating_value... Ts>
auto
geommean_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, T1 a1, Ts... args)
{
  return mask_op(cond, eve::geommean, a0, a1, args...);
}
}
