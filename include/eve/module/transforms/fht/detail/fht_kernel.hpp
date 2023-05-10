//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <vector>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/fht/utils.hpp>
#include <type_traits>

namespace eve::detail
{


  ////////////////////////////////////////////////////////////////////////////////////
  inline void hartley_shift_05(auto ff,auto n)
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

#define FINAL_RADIX_16 1
// Fast Hartley transform (FHT).
// Recursive decimation in frequency (DIF) algorithm.
// Excellent performance for large array sizes.

  EVE_FORCEINLINE constexpr void
  fht_loc_dif_core(auto f, auto log2_n, bool simd) noexcept
  // requires(std::is_floating_point_v<typename R::value_type>)
  {
    if ( log2_n<= 13 )  // sizeof(Type)*(2**threshold) <= L1_CACHE_BYTES
    {
      fht_dif_core(f, log2_n, simd);
      return;
    }
    else
    {
      using i_t = decltype(log2_n);
      for (i_t log2_m=log2_n; log2_m>=1; --log2_m)
      {
        const i_t m = (1UL<<log2_m);
        const i_t mh = (m>>1);
        auto f1 = eve::algo::as_range(f, f+mh);
        auto f2 = eve::algo::as_range(f+mh, f+2*mh);
        auto view = eve::views::zip(f1, f2);
        auto doit = [](auto zz, auto ignore){
          auto [f1_it, f2_it] = zz;
          auto [f1, f2] = eve::load[ignore](zz);
          sd(f1, f2);
          store[ignore](f1, f1_it);
          store[ignore](f2, f2_it);
        };
        eve::algo::for_each[eve::algo::unroll<2>](view, doit);

        hartley_shift_05(f+mh, mh);
      }
      for (i_t log2_m=1; log2_m<log2_n; ++log2_m)
        fht_loc_dif_core(f+(1UL<<log2_m), log2_m, simd);
    }
  }

  template <range  R, floating_scalar_value T>
  EVE_FORCEINLINE void fht_dif_loc_(EVE_SUPPORTS(cpu_)
                               , aos_type const &
                               , R& fr
                               , T fac
                               , bool simd = true)
  {
    auto n =  std::size(fr);
    auto log2_n = eve::countr_zero(n); //eve::log2(n));
    revbin_permute(fr);
    fht_loc_dif_core(fr.data(), log2_n, simd);
    scaleit(fr, fac);
  }

}
