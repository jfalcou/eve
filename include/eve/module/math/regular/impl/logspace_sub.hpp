//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/expm1.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/log1p.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<floating_ordered_value T, floating_ordered_value U>
EVE_FORCEINLINE auto
logspace_sub_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(logspace_sub, a, b);
}

template<floating_ordered_value T>
EVE_FORCEINLINE T
logspace_sub_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto x    = if_else(a == b, zero, b - a);
    auto test = x > -log_2(as(x));
    if( eve::all(test) ) return a + eve::log(-expm1(x));
    else if( eve::any(test) ) return a + if_else(test, log(-expm1(x)), log1p(-exp(x)));
    else return a + log1p(-exp(x));
  }
  else { return apply_over(logspace_sub, a, b); }
}

//===============================================================================================
// Multi case
//================================================================================================
template<floating_ordered_value T0, floating_ordered_value T1, floating_ordered_value... Ts>
auto
logspace_sub_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args) noexcept
-> common_value_t<T0, T1, Ts...>
{
  using r_t = common_value_t<T0, T1, Ts...>;
  if constexpr( has_native_abi_v<r_t> )
  {
    r_t  that(logspace_sub(a0, a1));
    auto lsub = [](auto that, auto next) -> r_t
    {
      that = logspace_sub(that, next);
      return that;
    };
    ((that = lsub(that, args)), ...);
    return that;
  }
  else { return apply_over(logspace_sub, a0, a1, args...); }
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
logspace_sub_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return logspace_sub(m...); }, tup);
}

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, floating_ordered_value U, floating_ordered_value V>
EVE_FORCEINLINE auto
logspace_sub_(EVE_SUPPORTS(cpu_),
              C const& cond,
              U const& t,
              V const& f) noexcept
-> decltype( if_else(cond, logspace_add(t, f), t) )
{
  return mask_op(cond, eve::logspace_sub, t, f);
}

}
