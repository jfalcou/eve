//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/transforms/utils.hpp>
#include <eve/module/transforms/fht/detail/fht_df_kernel.hpp>
#include <type_traits>

namespace eve::detail
{
  template<eve::algo::relaxed_range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  small_df_fht_(EVE_SUPPORTS(cpu_), R & fr, T fac, bool simd = true) noexcept
  {
    // better for size(fr) less than <= 64
    auto f = fr.data();
    auto n =  std::size(fr);
    auto l2_n = eve::countr_zero(n); //log2(n));
    if ( l2_n<=2 )
    {
      if ( l2_n==1 )
      {
        sd(f[0], f[1]);
      }
      else if ( l2_n==2 )
      {
        T f0, f1, f2, f3;
        sd(f[0], f[2], f0, f1);
        sd(f[1], f[3], f2, f3);
        sd(f0, f2, f[0], f[2]);
        sd(f1, f3, f[1], f[3]);
      }
      scaleit(fr, fac*invsqrt_2(as(fac)));
      return;
    }

    fht_df_kernel(f, l2_n, simd);
    revbin_permute(fr);
    scaleit(fr, fac*invsqrt_2(as(fac)));
  }
}
