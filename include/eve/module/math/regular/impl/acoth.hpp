//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/atanh.hpp>
#include <eve/module/math/regular/radindeg.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
acoth_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  if constexpr( has_native_abi_v<T> ) { return eve::atanh(rec(x)); }
  else { return apply_over(acoth, x); }
}
}
