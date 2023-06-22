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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/is_not_greater_equal.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/absmax.hpp>
#include <eve/module/core/regular/minus.hpp>

#include <type_traits>

namespace eve::detail
{

template<value  ...Ts>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_), Ts... args) noexcept
-> decltype(absmax(args...))
{
  return minus(absmax(args...));
}

template<conditional_expr C, value T0, value  ...Ts>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_), C const & c, T0 t0, Ts... args) noexcept
-> decltype(if_else(c, negabsmax(t0, args...), t0))
{
  return minus[c](absmax[c](t0, args...));
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
negabsmax_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return minus(abs(get<0>(tup)));
  else return kumi::apply( [&](auto... m) { return negabsmax(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
negabsmax_(EVE_SUPPORTS(cpu_), D const & d, Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return -d(eve::abs)(get<0>(tup));
  else return minus(kumi::apply( [&](auto... m) { return d(absmax)(m...); }, tup));
}

}