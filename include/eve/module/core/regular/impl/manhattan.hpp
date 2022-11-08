//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_infinite.hpp>

namespace eve::detail
{
//================================================================================================
// N parameters
//================================================================================================
template<value T0, value... Ts>
auto
manhattan_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 a0, Ts... args)
{
  auto r = eve::add(eve::abs(a0), eve::abs(args)...);
  auto inf_found = is_infinite(a0) || (... || is_infinite(args));
  return if_else(inf_found, inf(as(r)), r);
}

template<value T0, value... Ts>
auto
manhattan_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
{
  return eve::add(eve::abs(a0), eve::abs(args)...);
}

//================================================================================================
// tuples
//================================================================================================
template<kumi::non_empty_product_type Ts>
auto
manhattan_(EVE_SUPPORTS(cpu_), Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return abs(get<0>(tup));
  else return eve::abs(kumi::apply( [&](auto... m) { return manhattan(m...); }, tup));
}

template<kumi::non_empty_product_type Ts>
auto
manhattan_(EVE_SUPPORTS(cpu_), pedantic_type const& d, Ts tup)
{
  if constexpr( kumi::size_v<Ts> == 1) return abs(get<0>(tup));
  else return eve::abs(kumi::apply( [&](auto... m) { return pedantic(manhattan)(m...); }, tup));
}
// -----------------------------------------------------------------------------------------------
// Masked case
template<conditional_expr C, floating_value... Ts>
EVE_FORCEINLINE auto
manhattan_(EVE_SUPPORTS(cpu_), C const& cond, Ts... a) noexcept
{
  return mask_op(cond, eve::manhattan, a...);
}
}
