//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/algo.hpp>
#include <type_traits>

namespace eve::detail
{
  ////////////////////////////////////////////////////////////////////////////////////
  inline void ht_shft_scal(auto ff, auto n)
  // scalar version,  n must be a power of 2.
  {
    using i_t = decltype(n);
    using e_t =  std::remove_reference_t<decltype(ff[0])>;
    const double phi0 = rec(e_t(n));
    auto phi = zero(as(phi0));
    for (i_t i=1, j=n-1;  i<j;  ++i, --j)
    {
      phi += phi0;
      auto [c, s] = exp_ipi(phi);
      auto fi = ff[i];
      auto fj = ff[j];
      ff[i] = fi * c + fj * s;
      ff[j] = fi * s - fj * c;
    }
  }


  ////////////////////////////////////////////////////////////////////////////////////
  inline void ht_shft_simd(auto ff, auto n)
  // Optimized version,  n must be a power of 2.
  {
    using i_t = decltype(n);
    using e_t =  std::remove_reference_t<decltype(ff[0])>;
    constexpr i_t cardinal = eve::expected_cardinal_v<e_t>;
    auto phi0 = rec(e_t(n));
    auto phi = zero(as(phi0));
    const i_t nh = n/2;
    if ( n>=4 )
    {
      {
        i_t im=nh/2, jm=3*im;
        auto fi = ff[im],  fj = ff[jm];
        auto cs = invsqrt_2(as(fi));
        ff[im] = (fi + fj) * cs;
        ff[jm] = (fi - fj) * cs;
      }
      if ( n>=8 )
      {
        using we_t = eve::wide<e_t, eve::fixed<cardinal>>;
        we_t i0([](auto i,  auto ){ return e_t(i); });
        auto wcs = exp_ipi(i0*phi0);
        auto nfp = min(cardinal, n);
        for (i_t i=1, j=n-1, k=nh-1, l=nh+1;  (i < nfp)&&(i<k);  ++i, --j, --k, ++l)
        {
          phi += phi0;
          auto [c, s] = exp_ipi(phi);
          auto fi = ff[i];
          auto fj = ff[j];
          auto fk = ff[k];
          auto fl = ff[l];
          ff[i] = fi * c + fj * s;
          ff[j] = fi * s - fj * c;
          ff[k] = fk * s + fl * c;
          ff[l] = fk * c - fl * s;
        }
        if (n > 4*cardinal)
        {
          auto cs4 = wcs.get(cardinal-1)*wcs.get(1);
          auto siz = n/4-cardinal;
          using idx_t = as_integer_t<e_t>;
          auto is = eve::views::iota(idx_t(nfp), siz);
          auto phis = eve::views::iota_with_step(phi+phi0, phi0, siz);
          auto view = eve::views::zip(is, phis);
          auto doit = [cardinal, ff, n, nh, &wcs, cs4](auto zz, auto ignore){
            auto [ii, phi]= eve::load[ignore](zz);
            auto j = n-ii.get(cardinal-1) ;
            auto i = ii.get(0);
            auto l = i+nh;
            auto k = j-nh;
            auto fi = load[ignore](ff+i);
            auto fl = load[ignore](ff+i+nh);
            auto fk = reverse(load[ignore](ff+j-nh));
            auto fj = reverse(load[ignore](ff+j));
            wcs*= cs4;
            auto [c, s] = wcs;
            auto aa = fi * c + fj * s;
            auto bb = fi * s - fj * c;
            auto cc = fk * s + fl * c;
            auto dd = fk * c - fl * s;
            eve::store[ignore](aa, ff+i);
            eve::store[ignore](reverse(bb), ff+j);
            eve::store[ignore](dd, ff+l);
            eve::store[ignore](reverse(cc), ff+k);
          };
          eve::algo::for_each[eve::algo::unroll<2>](view, doit);
        }
      }
    }
  }
}
