//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/conditional.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
//================================================================================================
//== Masked case
//================================================================================================
template<conditional_expr C, value U, value... V>
EVE_FORCEINLINE auto
mul_(EVE_SUPPORTS(cpu_),
     C const& cond,
     U    t,
     V... f) noexcept
{
  return mask_op(cond, eve::mul, t, f...);
}

//================================================================================================
//==  regular N parameters
//================================================================================================
template<decorator D, value T0, value... Ts>
auto
mul_(EVE_SUPPORTS(cpu_), D const& d, T0 a0, Ts... args) noexcept
{
  common_value_t<T0, Ts...> that(a0);
  ((that = d(mul)(that, args)), ...);
  return that;
}

template<value T0, value... Ts>
auto
mul_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args) noexcept
-> common_value_t<T0, Ts...>
{
  auto that((a0 * ... * args));
  return that;
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
mul_(EVE_SUPPORTS(cpu_), Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return mul(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
mul_(EVE_SUPPORTS(cpu_), D const & d, Ts tup) noexcept
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return d(mul)(m...); }, tup);
}

}
