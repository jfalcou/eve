//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
template<real_value T0, real_value... Ts>
common_compatible_t<T0, Ts...>
hypot_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
{
  using r_t = common_compatible_t<T0, Ts...>;
  if constexpr( has_native_abi_v<r_t> )
  {
    r_t  that(sqr_abs(r_t(a0)));
    auto addsqrabs = [](auto that, auto next) -> r_t
    {
      auto anext = eve::abs(next);
      that       = fma(anext, anext, that);
      return that;
    };
    ((that = addsqrabs(that, args)), ...);
    return eve::sqrt(that);
  }
  else { return apply_over(hypot, r_t {a0}, r_t {args}...); }
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
hypot_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return abs(get<0>(tup));
  else return kumi::apply( [&](auto... m) { return hypot(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
hypot_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return abs(get<0>(tup));
  else return kumi::apply( [&](auto... m) { return d(hypot)(m...); }, tup);
}

// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, floating_value T0, floating_value... Ts>
auto
hypot_(EVE_SUPPORTS(cpu_), C const& cond, T0 a0, Ts... args)
{
  return mask_op(cond, eve::hypot, a0, args...);
}
}
