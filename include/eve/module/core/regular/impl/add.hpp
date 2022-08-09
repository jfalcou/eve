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
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, value U, value V>
EVE_FORCEINLINE auto
add_(EVE_SUPPORTS(cpu_),
     C const& cond,
     U const& t,
     V const& f) noexcept requires compatible_values<U, V>
{
  return mask_op(cond, eve::add, t, f);
}

//================================================================================================
// N parameters
//================================================================================================
template<decorator D, value T0, value... Ts>
auto
add_(EVE_SUPPORTS(cpu_), D const&, T0 a0, Ts... args) requires(compatible_values<T0, Ts>&&...)
{
  common_compatible_t<T0, Ts...> that(a0);
  ((that = D()(add)(that, args)), ...);
  return that;
}

template<value T0, value... Ts>
auto
add_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args) requires(compatible_values<T0, Ts>&&...)
{
  common_compatible_t<T0, Ts...> that(a0);
  ((that = add(that, args)), ...);
  return that;
}
}
