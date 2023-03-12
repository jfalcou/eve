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
template<ordered_value T, ordered_value U>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_),
        saturated_type const&,
        T const& a,
        U const& b) noexcept
-> decltype(maxabs(a, b))
{
  return arithmetic_call(saturated(maxabs), a, b);
}

template<ordered_value T>
EVE_FORCEINLINE auto
maxabs_(EVE_SUPPORTS(cpu_),
        saturated_type const&,
        T const& a,
        T const& b) noexcept requires has_native_abi_v<T>
{
  return eve::max(saturated(eve::abs)(a), saturated(eve::abs)(b));
}

//================================================================================================
// N parameters
//================================================================================================
template<ordered_value T0, ordered_value T1, ordered_value... Ts>
auto
maxabs_(EVE_SUPPORTS(cpu_), saturated_type const&, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(maxabs(a0, a1, args...))
{
  auto sa = saturated(eve::abs);
  return eve::max(sa(a0), sa(a1), sa(args)...);
}
}
