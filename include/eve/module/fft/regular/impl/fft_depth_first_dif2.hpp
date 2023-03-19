//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>

namespace eve::detail
{

  template<value T, value T1>
  EVE_FORCEINLINE constexpr auto
  fft_depth_first_dif2(EVE_SUPPORTS(cpu_), std::vector<as_complex<T>> const & a, T1 s, T1 f) noexcept
  {
    using  c_t = complex<T>;
    auto n =  a.size();
    using i_t = decltype(N);
    EVE_ASSERT(is_pow2(N),  "data size is not a power of 2"); 
    std::vector<c_t> c(N);
    auto ldn = i_t(eve::log2(n)); 
    for (i_t ldm=ldn; ldm>=1; --ldm)
    {
      const i_t mh = N >> 1;
      const double phi = s / T(mh);
      for (i_t r=0; r<n; r+=m)
      {
        for (i_t j=0; j<mh; ++j)
        {
          i_t i0 = r + j;
          i_t i1 = i0 + mh;

          auto u = f[i0];
          auto v = f[i1];

          f[i0] = (u + v);
          f[i1] = (u - v) *  exp_ipi( phi*j );
        }
      }
    }

    revbin_permute(f, n);

    

  }

}
