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
#include <eve/module/transforms/fht.hpp>
#include <eve/concept/range.hpp>


namespace eve::detail
{
  template <typename T>
  void inline
  fht_convolution_kernel(const T * f, T *  g, auto n,
                         T v = T(0)) noexcept

  // ldn := base-2 logarithm of the array length.
  // v!=0.0 chooses alternative normalization.
  {
    using i_t = decltype(n);
    if ( v==0.0 ) v = rec(T(n));
    g[0] *= (v * f[0]);
    const i_t nh = n/2;
    if ( is_eqz(nh) ) return;

    g[nh] *= (v * f[nh]);
    v *= 0.5;
    auto mul = [v](auto xi, auto xj, auto &yi, auto & yj)
    {
      using e_t = decltype(xi);
      e_t h1p = xi, h1m = xj;
      e_t s1 = h1p + h1m;
      e_t d1 = h1p - h1m;
      e_t h2p = yi, h2m = yj;
      yi = (h2p * s1 + h2m * d1) * v;
      yj = (h2m * s1 - h2p * d1) * v;
    };
    for (i_t i=1,j=n-1; i<j; i++,j--)  mul(f[i], f[j], g[i], g[j]);
  }

  template<range R>
  EVE_FORCEINLINE constexpr void
  fht_cyclic_convolution_(EVE_SUPPORTS(cpu_), aos_type const &, R aa, R bb, R & cc) noexcept
  {
    EVE_ASSERT(std::size(aa) == std::size(bb), "aa and bb  must have  the same size");
    EVE_ASSERT(std::size(aa) == std::size(cc), "aa and cc  must have  the same size");
    auto a = aa.data();
    auto b = bb.data();
    auto c = cc.data();
    auto n = std::ssize(aa);
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(aa[0])>>;

    aos(large_fht)(aa, e_t(1));
    aos(large_fht)(bb, e_t(1));
    fht_convolution_kernel(a, b, n, rsqrt(e_t(n)));
    pr("bb", bb.data(), n);
    std::memcpy(c, b, n*sizeof(e_t));
  }

  template<range R>
  EVE_FORCEINLINE constexpr void
  fht_linear_convolution_(EVE_SUPPORTS(cpu_), aos_type const &, R aa, R bb, R & cc) noexcept
  {
    EVE_ASSERT(std::size(aa) == std::size(bb), "aa and bb  must have  the same size");
    EVE_ASSERT(std::size(cc) == 2*std::size(aa), "cc must have 2 times the size of a");
    auto n = std::ssize(aa);
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(aa[0])>>;
    std::vector < e_t> da(aa), db(bb);
    da.resize(2*n); pr("da", da.data(), 2*n);
    db.resize(2*n); pr("db", db.data(), 2*n);
    aos(large_fht)(da, e_t(1));
    aos(large_fht)(db, e_t(1));
    fht_convolution_kernel(da.data(), db.data(), 2*n, rsqrt(e_t(n))/2);
    aos(large_fht)(db, e_t(1));
    pr("db", db.data(), 2*n);
    std::memcpy(cc.data(), db.data(), 2*n*sizeof(e_t));
  }
}
