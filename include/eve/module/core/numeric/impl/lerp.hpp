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
#include <eve/module/core/numeric/fma.hpp>
#include <eve/module/core/numeric/fnma.hpp>
#include <eve/module/core/regular/all.hpp>

#include <type_traits>

namespace eve::detail
{
template<floating_real_value T, floating_real_value U, floating_real_value V>
EVE_FORCEINLINE auto
lerp_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, U const& b, V const& t) noexcept
-> decltype(lerp(a, b, t))
{
  return arithmetic_call(numeric(lerp), a, b, t);
}

template<floating_real_value T>
EVE_FORCEINLINE T
lerp_(EVE_SUPPORTS(cpu_), numeric_type const&, T const& a, T const& b, T const& t) noexcept
{
  return numeric(fma)(t, b, numeric(fnma)(t, a, a));
}
}
