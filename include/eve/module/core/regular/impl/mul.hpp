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
#include <eve/detail/function/conditional.hpp>
#include <eve/detail/function/operators.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/detail/multi_mul.hpp>
#include <eve/traits/common_compatible.hpp>

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
template<value T0, value T1, value... Ts>
common_compatible_t<T0, T1, Ts...>
mul_(EVE_SUPPORTS(cpu_), T0 a0, T1 a1, Ts... args)
{
  using r_t = common_compatible_t<T0, T1, Ts...>;
  r_t that(mul(r_t(a0), r_t(a1)));
  ((that = mul(that, r_t(args))), ...);
  return that;
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
mul_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return mul(m...); }, tup);
}

template<decorator D, kumi::non_empty_product_type Ts>
auto
mul_(EVE_SUPPORTS(cpu_), D const & d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
  else return kumi::apply( [&](auto... m) { return d(mul)(m...); }, tup);
}


}
