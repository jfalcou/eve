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
#include <eve/module/core/numeric/absmin.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
negabsmin_(EVE_SUPPORTS(cpu_),
           numeric_type const&,
           T const& a,
           U const& b) noexcept
-> decltype(negabsmin(a, b))
{
  return arithmetic_call(numeric(negabsmin), a, b);
}

template<value T>
EVE_FORCEINLINE auto
negabsmin_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b) noexcept
{
  return minus(numeric(absmin)(a, b));
}

//================================================================================================
// N parameters
//================================================================================================
template<value T0, value T1, value... Ts>
auto
negabsmin_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(negabsmin(a0,a1, args...))
{
  return minus(numeric(eve::absmin)(a0, a1, args...));
}

}
