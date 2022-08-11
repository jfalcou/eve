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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/minabs.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_),
           saturated_type const&,
           T const& a,
           U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(saturated(negminabs), a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_),
           saturated_type const&,
           T const& a,
           T const& b) noexcept requires has_native_abi_v<T>
{
  return -saturated(minabs(a, b));
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
auto
negminabs_(EVE_SUPPORTS(cpu_), saturated_type const&, T0 a0, T1 a1, Ts... args)
{
  return -saturated(eve::minabs)(a0, a1, args...);
}

}
