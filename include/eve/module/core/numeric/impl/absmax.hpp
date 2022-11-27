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
#include <eve/module/core/numeric/max.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
template<real_value T, real_value U>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_),
        numeric_type const&,
        T const& a,
        U const& b) noexcept
-> decltype(absmax(a, b))
{
  return arithmetic_call(numeric(absmax), a, b);
}

template<real_value T>
EVE_FORCEINLINE auto
absmax_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b) noexcept
{
  return eve::abs(eve::numeric(max)(a, b));
}

//================================================================================================
// N parameters
//================================================================================================
template<real_value T0, value T1, value... Ts>
auto
absmax_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 a0, T1 a1, Ts... args)
  -> decltype(absmax(a0, a1, args...))
{
  return eve::abs(numeric(eve::max)(a0, a1, args...));
}

}
