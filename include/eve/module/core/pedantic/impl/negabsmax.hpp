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
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/pedantic/absmax.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/saturated/abs.hpp>
#include <eve/platform.hpp>

#include <type_traits>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_),
           pedantic_type const&,
           T const& a,
           U const& b) noexcept
-> decltype(negabsmax(a, b))
{
  return arithmetic_call(pedantic(negabsmax), a, b);
}

template<value T>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a, T const& b) noexcept
{
  return minus(pedantic(absmax)(a, b));
}

//================================================================================================
// N parameters
//================================================================================================
template<value T0, value T1, value... Ts>
auto
negabsmax_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 a0, T1 a1, Ts... args)
{
  return minus(pedantic(eve::absmax)(a0, a1, args...));
}
}
