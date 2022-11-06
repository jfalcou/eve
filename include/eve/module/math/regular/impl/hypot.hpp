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
template<value T0, value... Ts>
auto
hypot_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
{
  using c_t = common_compatible_t<T0, Ts...>;
  if constexpr( has_native_abi_v<c_t> )
  {
    using r_t = decltype(eve::abs(c_t{}));
    r_t  that(eve::sqr(eve::abs(a0)));
    auto addsqrabs = [](auto that, auto next) -> r_t
      {
        auto anext = eve::abs(next);
        that       = fma(anext, anext, that);
        return that;
      };
    ((that = addsqrabs(that, args)), ...);
    return eve::sqrt(that);
  }
  else { return apply_over(hypot, eve::abs(a0), eve::abs(args)...); }
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
