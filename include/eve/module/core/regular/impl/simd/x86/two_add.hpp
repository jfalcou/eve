//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once
#include <eve/module/core/regular/maxmag.hpp>
#include <eve/module/core/regular/minmag.hpp>


namespace eve::detail
{
  template<callable_options O, typename T>
  constexpr EVE_FORCEINLINE auto two_add_(EVE_REQUIRES(avx512_), O const&, T a, T b)
  {
    // maxmag/maxmag have an intrinsic in avx512 so we gain one operation
    auto r0 = a + b;
    auto maxi = maxmag(a, b);
    auto mini = minmag(a, b);
    auto r1 = mini - (r0-maxi);
    if constexpr( eve::platform::supports_infinites )
      r1 = if_else(is_infinite(r0), eve::zero, r1);

    return eve::zip(r0, r1);
  }
}
