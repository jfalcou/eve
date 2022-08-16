//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math/constant/pio_2.hpp>
#include <eve/module/math/regular/atan.hpp>
#include <eve/module/math/regular/sinh.hpp>

namespace eve::detail
{

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
invgd_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    return if_else(abs(x) <= pio_2(as(x)), atanh(sin(x)), allbits);
  }
  else return apply_over(invgd, x);
}
}
