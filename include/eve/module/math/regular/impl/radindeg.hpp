//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
radindeg_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto radradindeg  = Ieee_constant<T, 0X42652EE1U, 0X404CA5DC1A63C1F8ULL>();
    auto radradindegr = Ieee_constant<T, 0X353387C0U, 0X3CE1E7AB456405F8ULL>();
    return fma(a, radradindegr, a * radradindeg);
  }
  else return apply_over(radindeg, a);
}

}
