//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/transforms/utils.hpp>
#include <eve/concept/range.hpp>


namespace eve::detail
{

  template<range R>
  EVE_FORCEINLINE constexpr void
  naive_cyclic_convolution_(EVE_SUPPORTS(cpu_), R aa, R bb, R & cc) noexcept
  {
    EVE_ASSERT(std::size(aa) == std::size(bb), "aa and bb  must have  the same size");
    EVE_ASSERT(std::size(aa) == std::size(cc), "aa and cc  must have  the same size");
    auto n = std::ssize(aa); //needs to be signed
    auto a = aa.data();
    auto b = bb.data();
    auto c = cc.data();
    using i_t = decltype(n);
    using e_t =  std::remove_reference_t<decltype(a[0])>;
    for (i_t m=0; m<n; ++m)
    {
      e_t s = 0;
      for (i_t k=0; k<n; ++k)
      {
        i_t k2 = m - k;
        if ( is_ltz(k2) ) k2 += n;
        s = fam(s, a[k], b[k2]);
      }
      c[m] = s;
    }
  }

  template<range R>
  EVE_FORCEINLINE constexpr void
  naive_linear_convolution_(EVE_SUPPORTS(cpu_), R aa, R bb, R & cc) noexcept
  {
    EVE_ASSERT(std::size(aa) == std::size(bb), "aa and bb  must have  the same size");
    EVE_ASSERT(std::size(cc) == 2*std::size(aa), "cc must have 2 times the size of a");
    auto a = aa.data();
    auto b = bb.data();
    auto c = cc.data();
    auto n = std::size(aa);
    using i_t = decltype(n);
    using e_t =  std::remove_reference_t<decltype(a[0])>;
    for (i_t m=0; m<n; ++m)
    {
      e_t s0 = 0;
      for (i_t k=0, k2=m; k<=m; ++k, --k2)  s0 = fam(s0, a[k], b[k2]);
      c[m] = s0;
      e_t s1 = 0;
      for (i_t k2=n-1, k=m+1; k<n; ++k, --k2)  s1 = fam(s1, a[k], b[k2]);
      c[n+m] = s1;
    }
  }
}
