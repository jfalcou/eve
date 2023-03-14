//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/common_value.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/decorator/numeric.hpp>
#include <eve/module/core/numeric/maxabs.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
negmaxabs_(EVE_SUPPORTS(cpu_),
           numeric_type const&,
           T const& a,
           U const& b) noexcept
-> decltype(negmaxabs(a, b))
{
  return arithmetic_call(numeric(negmaxabs), a, b);
}

template<value T>
EVE_FORCEINLINE auto
negmaxabs_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b) noexcept
{
  return minus(numeric(maxabs)(a, b));
}

//================================================================================================
// N parameters
//================================================================================================
template<value T0, value T1, value... Ts>
auto
negmaxabs_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 a0, T1 a1, Ts... args) noexcept
  -> decltype(negmaxabs(a0, a1, args...))
{
  return minus(numeric(eve::maxabs)(a0, a1, args...));
}

}
