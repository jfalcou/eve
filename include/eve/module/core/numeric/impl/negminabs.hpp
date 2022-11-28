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
#include <eve/module/core/numeric/minabs.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
template<value T, value U>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_),
           numeric_type const&,
           T const& a,
           U const& b) noexcept
-> decltype(negminabs(a, b))
{
  return arithmetic_call(numeric(negminabs), a, b);
}

template<value T>
EVE_FORCEINLINE auto
negminabs_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b) noexcept
{
  return minus(numeric(minabs)(a, b));
}

//================================================================================================
// N parameters
//================================================================================================
template<value T0, value T1, value... Ts>
auto
negminabs_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 a0, T1 a1, Ts... args)
  -> decltype(negminabs(a0, a1, args...))
{
  return minus(numeric(eve::minabs)(a0, a1, args...));
}

}
