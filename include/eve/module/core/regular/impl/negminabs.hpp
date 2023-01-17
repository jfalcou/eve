//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/regular/minabs.hpp>
#include <eve/module/core/regular/minus.hpp>

namespace eve::detail
{

template<value  ...Ts>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_), Ts... args) noexcept
-> decltype(minus(minabs(args...)))
{
  return minus(minabs(args...));
}

template<conditional_expr C, value T0, value  ...Ts>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_), C const & c, T0 t0, Ts... args) noexcept
-> decltype(if_else(c, negminabs(t0, args...), t0))
{
  return minus[c](minabs[c](t0, args...));
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
negminabs_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return minus(abs(get<0>(tup)));
  else return kumi::apply( [&](auto... m) { return negminabs(m...); }, tup);
}


template<decorator D, kumi::non_empty_product_type Ts>
auto
negminabs_(EVE_SUPPORTS(cpu_), D const & d , Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return minus(abs(get<0>(tup)));
  else return minus(kumi::apply( [&](auto... m) { return d(minabs)(m...); }, tup));
}

}
