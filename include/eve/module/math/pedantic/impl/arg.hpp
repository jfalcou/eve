//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE constexpr auto
arg_(EVE_SUPPORTS(cpu_), pedantic_type const&, T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto z = if_else(is_negative(a), pi(eve::as(a)), eve::zero);
    if constexpr( platform::supports_nans ) { return if_else(is_nan(a), eve::allbits, z); }
    else { return z; }
  }
  else { return apply_over(pedantic(arg), a); }
}
}
