//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/asin.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
acsc_(EVE_SUPPORTS(cpu_), T const& a0) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return eve::asin(rec(a0)); }
  else { return apply_over(acsc, a0); }
}
}
