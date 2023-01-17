//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/regular/maxabs.hpp>
#include <eve/module/core/regular/minus.hpp>

#include <type_traits>

namespace eve::detail
{

template<value  ...Ts>
EVE_FORCEINLINE auto
negmaxabs_(EVE_SUPPORTS(cpu_), Ts... args)
-> decltype(minus(maxabs(args...)))
{
  return minus(maxabs(args...));
}

template<conditional_expr C, value T0, value  ...Ts>
EVE_FORCEINLINE auto
negmaxabs_(EVE_SUPPORTS(cpu_), C const & c, T0 t0, Ts... args)
-> decltype(if_else(c, negmaxabs(t0, args...), t0))
{
  return minus[c](maxabs[c](t0, args...));
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
negmaxabs_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return minus(abs(get<0>(tup)));
  else return kumi::apply( [&](auto... m) { return negmaxabs(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
negmaxabs_(EVE_SUPPORTS(cpu_), D const & d , Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return minus(abs(get<0>(tup)));
  else return minus(kumi::apply( [&](auto... m) { return d(maxabs)(m...); }, tup));
}
}
