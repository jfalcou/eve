//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{

  template < auto N, typename T>
  EVE_FORCEINLINE constexpr void
  unroll(T * f, auto n,  auto step, auto doit) noexcept // 8 elements
  {
    auto n1 = n%(N*step);
    auto n2 = n-n1*step;
    auto fi = f;
   for(auto i = 0; i < n2; i+= step*N, fi+= step*N)
    {
      if constexpr(N == 1)
      {
        doit(fi);
      }
      else if constexpr(N == 2)
      {
        doit(fi); doit(fi+step);
      }
      else if constexpr(N == 4)
      {
        doit(fi); doit(fi+step); doit(fi+2*step); doit(fi+3*step);
      }
      else if constexpr(N == 8)
      {
        doit(fi);        doit(fi+step);   doit(fi+2*step); doit(fi+3*step);
        doit(fi+4*step); doit(fi+5*step); doit(fi+6*step); doit(fi+7*step);
      }
    }
    for(auto i = n2; i < n; i+= step) doit(fi);
  }
}
