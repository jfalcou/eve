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
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/saturated/abs.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_),
        saturated_type const&,
        T const& a,
        U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(saturated(absmin), a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
absmin_(EVE_SUPPORTS(cpu_),
        saturated_type const&,
        T const& a,
        T const& b) noexcept requires has_native_abi_v<T>
{
  return saturated(eve::abs)(eve::min(a, b));
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
auto
absmin_(EVE_SUPPORTS(cpu_), saturated_type const&, T0 a0, T1 a1, Ts... args)
{
  return saturated(eve::abs)(eve::min(a0, a1, args...));
}

}
