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
  template<typename T, callable_options O>
  constexpr EVE_FORCEINLINE T
  signgam_(EVE_REQUIRES(cpu_), O const &, T a0)
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
