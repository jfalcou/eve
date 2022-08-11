//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/numeric/absmax.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_),
           numeric_type const&,
           T const& a,
           U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(numeric(negabsmax), a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
negabsmax_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b) noexcept
{
  return -numeric(absmax)(a, b);
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, real_value T1, real_value... Ts>
auto
negabsmax_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 a0, T1 a1, Ts... args)
{
  return -numeric(eve::absmax)(a0, a1, args...);
}

}
