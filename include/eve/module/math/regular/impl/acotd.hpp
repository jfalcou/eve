//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/acot.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
acotd_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return radindeg(acot(a)); }
  else { return apply_over(acotd, a); }
}
}
