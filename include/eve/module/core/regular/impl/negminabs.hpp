//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/module/core/regular/minabs.hpp>
#include <eve/module/core/regular/minus.hpp>

namespace eve::detail
{

template<typename  ...Ts>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_), Ts... args)
{
  return minus(minabs(args...));
}

template<conditional_expr C, typename  ...Ts>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_), C const & c, Ts... args)
{
  return minus[c](minabs[c](args...));
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_tuple Ts>
auto
negminabs_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return minus(abs(get<0>(tup)));
  else return kumi::apply( [&](auto... m) { return negminabs(m...); }, tup);
}


template<decorator D, kumi::non_empty_tuple Ts>
auto
negminabs_(EVE_SUPPORTS(cpu_), D const & d , Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return minus(abs(get<0>(tup)));
  else return minus(kumi::apply( [&](auto... m) { return d(minabs)(m...); }, tup));
}

}
