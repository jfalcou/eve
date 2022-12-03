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
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/minus.hpp>

#include <type_traits>

namespace eve::detail
{

template<typename  ...Ts>
EVE_FORCEINLINE auto
negabsmin_(EVE_SUPPORTS(cpu_), Ts... args) noexcept
-> decltype(absmax(args...))
{
  return minus(absmin(args...));
}

template<conditional_expr C, typename T0, typename  ...Ts>
EVE_FORCEINLINE auto
negabsmin_(EVE_SUPPORTS(cpu_), C const & c, T0 t0, Ts... args) noexcept
-> decltype(if_else(c, negabsmin(t0, args...), t0))
{
  return minus[c](absmin[c](t0, args...));
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
negabsmin_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return minus(get<0>(tup));
  else return kumi::apply( [&](auto... m) { return negabsmin(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
negabsmin_(EVE_SUPPORTS(cpu_), D const & d, Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return -d(eve::abs)(get<0>(tup));
  else return minus(kumi::apply( [&](auto... m) { return d(absmin)(m...); }, tup));
}

}
