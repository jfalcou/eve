//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>

namespace eve::detail
{
// -----------------------------------------------------------------------------------------------
// regular case
template<real_value T, real_value U>
EVE_FORCEINLINE auto
dist_(EVE_SUPPORTS(cpu_), T const& a, U const& b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(dist, a, b);
}

template<real_value T>
EVE_FORCEINLINE T
dist_(EVE_SUPPORTS(cpu_), T const& a, T const& b) noexcept requires has_native_abi_v<T>
{
  return eve::max(a, b) - eve::min(a, b);
}
}
