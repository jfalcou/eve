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

namespace eve::detail
{

//================================================================================================
// Masked case
//================================================================================================
template<conditional_expr C, value U, value... Vs>
EVE_FORCEINLINE auto
sub_(EVE_SUPPORTS(cpu_),
     C const& cond,
     U  t,
     Vs ... fs) noexcept
{
  return mask_op(cond, eve::sub, t, fs...);
}

//================================================================================================
// N parameters
//================================================================================================
template<decorator D, real_value T0, real_value... Ts>
auto
sub_(EVE_SUPPORTS(cpu_), D const&, T0 a0, Ts... args) requires(compatible_values<T0, Ts>&&...)
{
  common_compatible_t<T0, Ts...> that(a0);
  ((that = D()(sub)(that, args)), ...);
  return that;
}

template<real_value T0, real_value... Ts>
auto
sub_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args) requires(compatible_values<T0, Ts>&&...)
{
  common_compatible_t<T0, Ts...> that(a0);
  ((that = sub(that, args)), ...);
  return that;
}
}
