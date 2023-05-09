//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/transforms/utils.hpp>
#include <eve/module/transforms/fht/detail/fht_dt_kernel.hpp>
#include <type_traits>

namespace eve::detail
{
  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  small_dt_fht_(EVE_SUPPORTS(cpu_), aos_type const &, R & fr, T fac, bool simd = true) noexcept
  {
    // "Small" Hartley Transform decimation in time
    // better for size(fr) <= 64
    auto f = fr.data();
    auto n =  std::size(fr);
    auto log2_n = eve::countr_zero(n); //eve::log2(n));
    if ( log2_n<=2 )
    {
      if ( log2_n==1 )  // two point fht
      {
        sd(f[0], f[1]);
      }
      else if ( log2_n==2 )  // four point fht
      {
        T f0, f1, f2, f3;
        sd(f[0], f[2], f0, f1);
        sd(f[1], f[3], f2, f3);
        sd(f0, f2, f[0], f[2]);
        sd(f1, f3, f[1], f[3]);
      }
      aos(scaleit)(fr, fac*invsqrt_2(as(fac)));
      return;
    }

    aos(revbin_permute)(fr);
    fht_dt_kernel(f, log2_n, simd);
    aos(scaleit)(fr, fac*invsqrt_2(as(fac)));
  }
}
