//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE constexpr T
signgam_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto isleza0 = is_ngtz(a0);
    auto a       = if_else(is_flint(a0) || is_infinite(a0),
                     eve::allbits,
                     oneminus(binarize(is_odd(floor(a0))) * T(2)));
    a            = if_else(is_eqz(a0), bit_or(one(as(a0)), bitofsign(a0)), a);
    return if_else(is_nan(a0), a0, if_else(isleza0, a, eve::one));
  }
  else return apply_over(signgam, a0);
}
}
