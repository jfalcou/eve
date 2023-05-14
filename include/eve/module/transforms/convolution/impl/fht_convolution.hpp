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
//    using e_t =  std::remove_reference_t<decltype(f[0])>;
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

//     constexpr i_t cardinal = expected_cardinal_v<e_t>;
//     auto nfp = min(cardinal, n);
//     for (i_t i=1, j=n-1; (i < j) && (i<nfp);  ++i, --j)
//     {
//       mul(f[i], f[j], g[i], g[j]);
//     }
//     if (n > 2*cardinal)
//     {

//       auto ff = f;
//       auto gg = g;

//       auto fi = eve::algo::as_range(ff+cardinal,ff+n/2);
//       auto fj = eve::views::reverse(eve::algo::as_range(ff+n/2+1, ff+n-cardinal+1));
//       auto gi = eve::algo::as_range(gg+cardinal,gg+n/2);
//       auto gj = eve::views::reverse(eve::algo::as_range(gg+n/2+1, gg+n-cardinal+1));

//       auto view = eve::views::zip(fi, fj, gi, gj);
//       auto doit = [mul, ff, gg](auto zz, auto ignore){
//         auto [fi_it, fj_it, gi_it, gj_it]= zz;
//         auto [fi, fj, gi, gj] = eve::load[ignore](zz);
//         mul(fi, fj, gi, gj);
//         eve::store[ignore](fi, fi_it);
//         eve::store[ignore](fj, fj_it);
//         eve::store[ignore](gi, gi_it);
//         eve::store[ignore](gj, gj_it);
//       };
//       eve::algo::for_each[eve::algo::unroll<2>][eve::algo::no_aligning](view, doit);
//     }
  }

  template <typename T>
  void inline
  fht_convolution_revbin_permuted_core(const T* f,
                                       T * g,
                                       auto n,
                                       T v = T(0))   noexcept
  {
    using i_t = decltype(n);
    if ( v==0.0 ) v = rec(T(n));
    g[0] *= (v * f[0]);
    if ( n >=2 )  g[1] *= (v * f[1]);  // 1 == revbin(nh)
    if ( n<4 )  return;

    v *= half(as(v));
    const i_t nh = (n>>1);
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
    i_t r=nh, rm=n-1;  // nh == revbin(1),  n1-1 == revbin(n-1)
    mul(f[r], f[rm], g[r], g[rm]);

    i_t k=2, km=n-2;
    std::cout << " r "<< r << std::endl; ;
    while ( k<nh  )
    {
std::cout << " k "<< k << std::endl;
      // k even:
      rm -= nh;
      i_t tr = r;
      r^=nh;
      for (i_t m=(nh>>1); !((r^=m)&m); m>>=1)  {
        std::cout << " m " << m << " r " << r << " " << std::endl;;
      }
      std::cout << "r final " << r << std::endl;
      mul(f[r], f[rm], g[r], g[rm]);
      --km;
      ++k;

      // k odd:
      rm += (tr-r);
      r += nh;
      mul(f[r], f[rm], g[r], g[rm]);
      --km;
      ++k;
    }
  }

//   template<range R>
//   EVE_FORCEINLINE constexpr void
//   fht_cyclic_convolution_(EVE_SUPPORTS(cpu_), R aa, R bb, R & cc) noexcept
//   {
//     EVE_ASSERT(std::size(aa) == std::size(bb), "aa and bb  must have  the same size");
//     EVE_ASSERT(std::size(aa) == std::size(cc), "aa and cc  must have  the same size");
//     auto a = aa.data();
//     auto b = bb.data();
//     auto c = cc.data();
//     auto n = std::ssize(aa);
//     using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(aa[0])>>;

//     large_df_fht(aa, e_t(1));
//     large_df_fht(bb, e_t(1));
//     fht_convolution_kernel(a, b, n, rsqrt(e_t(n)));
//     large_df_fht(bb, e_t(1));
//     pr("bb", bb.data(), n);
//     std::memcpy(c, b, n*sizeof(e_t));
//   }

  template<eve::algo::relaxed_range R>
  EVE_FORCEINLINE constexpr void
  fht_cyclic_convolution_(EVE_SUPPORTS(cpu_), R aa, R bb, R & cc) noexcept
  {
    auto a = aa.data();
    auto b = bb.data();
    auto n = min(std::size(aa), std::size(bb));
    cc.resize(n);
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(aa[0])>>;
    auto l2_n = eve::countr_zero(n); //eve::log2(n));
    fht_loc_df_core(a, l2_n, true);
    fht_loc_df_core(b, l2_n, true);
    fht_convolution_revbin_permuted_core(a, b, n);
    fht_loc_dt_core(b, l2_n, true);
    std::memcpy(cc.data(), b, n*sizeof(e_t));
  }



  template<eve::algo::relaxed_range R>
  EVE_FORCEINLINE constexpr void
  fht_linear_convolution_(EVE_SUPPORTS(cpu_), R aa, R bb, R & cc) noexcept
  {
    auto n2 = 2*min(std::size(aa), std::size(bb));
    aa.resize(n2);
    bb.resize(n2);
    fht_cyclic_convolution(aa, bb, cc);
  }
}
