//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/saturated/abs.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_),
           saturated_type const&,
           T const& a,
           U const& b) noexcept
-> decltype(negabsmax(a, b))
{
  return arithmetic_call(saturated(negabsmax), a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_),
           saturated_type const&,
           T const& a,
           T const& b) noexcept requires has_native_abi_v<T>
{
  return minus(saturated(eve::abs)(eve::max(a, b)));
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
auto
negabsmax_(EVE_SUPPORTS(cpu_), saturated_type const&, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(negabsmax(a0, a1, args...))
{
  return minus(saturated(eve::abs)(eve::max(a0, a1, args...)));
}

}
