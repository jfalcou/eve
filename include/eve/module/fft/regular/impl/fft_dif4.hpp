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
#include <eve/module/algo.hpp>
#include <eve/concept/range.hpp>
#include <vector>
#include <eve/module/fft/utils.hpp>

namespace eve::detail
{
  ///////////////////////////////////////////////////////////////////
  // fft decimation in frequency radix 4

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_dif4_(EVE_SUPPORTS(cpu_), aos_type const &
              , R & fr
              , R & fi
              , T fac) noexcept
  //  requires(eve::is_complex_v<typename R::value_type>)
  {
    aos(revbin_permute)(fr);
    aos(revbin_permute)(fi);
    //    using c_t = eve::complex<T>;
    auto n =  fr.size();
    using i_t = decltype(n);
    i_t lx = 2;
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    auto ldn = eve::countr_zero(n); //eve::log2(n));
    auto sumdiff = [](auto &a, auto &b){
      // {a, b}  <--| {a+b, a-b}
      auto t=a-b; a+=b; b=t;
    };
    auto sumdiffb = [](auto a, auto b, auto &s, auto &d){
      // {s, d}  <--| {a+b, a-b}
      s=a+b; d=a-b;
    };

    auto diffsum3 = [](auto a, auto &b, auto &s){
      // {a, b, s} <--| {a, a-b, a+b}  (used in split-radix FFTs)
      // NEVER call like func(a,b,a) or func(a,b,b)
      s=a+b; b=a-b;
    };


    auto sumdiff3_r = [](auto &a, auto b, auto &d){
      // {a,b,d} <--| {a+b, b, b-a}  (used in split-radix FFTs)
      // NEVER call like func(a,b,a) or func(a,b,b)
      d=b-a; a+=b;
    };

//     auto pr = [](auto name, auto v){
//       std::cout << name << " = (";
//       for(size_t i=0; i < v.size() ; ++i) std::cout << v[i] << " ";
//       std::cout << ")\n";
//     };
//     auto pr1 = [n](auto name, auto pr){
//       std::cout << name << " = (";
//       for(size_t i=0; i < n ; ++i) std::cout << *(pr+i) << " ";
//       std::cout << ")\n";
//     };
//     pr("fr ", fr);
//     pr("fi ", fi);
    auto frbeg = fr.begin();
    auto fibeg = fi.begin();
    if ( n<=2 )
    {
      if ( n==2 )
      {
        sumdiff(*frbeg, *(frbeg+1));
        sumdiff(*fibeg, *(fibeg+1));
      }
      return;
    }
    i_t lx2 = lx << 1;

    for (i_t ldm=ldn; ldm >= lx2; ldm-=lx)
    {
      i_t m = (1UL<<ldm);
      i_t m4 = (m>>lx);
      auto ph = T(0);
      const auto ph0 = T(2)/m;


//       if(m4 >= eve::nofs_cardinal_v<T>)
//       {
// //         std::cout << "simd" << std::endl;
//         auto js = eve::views::iota(T{0}, m4);
//         auto phs= eve::views::iota_with_step(T{0}, ph0, m4);
//         auto view = eve::views::zip(js, phs);
//         auto doit = [n, m, m4, &fr, &fi, sumdiff, sumdiff3_r, sumdiffb](auto zz, auto ignore){
//           auto [j, ph] = load[ignore](zz);
//           auto cs  = exp_ipi(ph);
//           using c_t =  decltype(cs);
//           auto cs2 = sqr(cs);
//           auto cs3 = cs2*cs;
//           for (i_t r=0; r<n; r+=m)
//           {
//             i_t i0 = j.get(0) + r;
//             i_t i1 = i0 + m4;
//             i_t i2 = i1 + m4;
//             i_t i3 = i2 + m4;
//             auto frbeg = fr.data();
//             auto fibeg = fi.data();
//             auto fri0 = load(frbeg+i0);
//             auto fri1 = load(frbeg+i1);
//             auto fri2 = load(frbeg+i2);
//             auto fri3 = load(frbeg+i3);
//             auto fii0 = load(fibeg+i0);
//             auto fii1 = load(fibeg+i1);
//             auto fii2 = load(fibeg+i2);
//             auto fii3 = load(fibeg+i3);
//             auto [xr, xi] = cs2*c_t(fri1, fii1);
//             using wT_t = decltype(xr);
//             wT_t ur, ui;
//             sumdiff3_r(xr, fri0, ur);
//             sumdiff3_r(xi, fii0, ui);

//             auto [yr, vr] = cs*c_t(fri2, fii2);
//             auto [vi, yi] = cs3*c_t(fri3, fii3);

//             sumdiff(yr, vi);
//             sumdiff(yi, vr);

//             sumdiffb(ur, vr, fri1, fri3);
//             sumdiffb(ui, vi, fii1, fii3);
//             sumdiffb(xr, yr, fri0, fri2);
//             sumdiffb(xi, yi, fii0, fii2);
//             store(fri0, frbeg+i0);
//             store(fri1, frbeg+i1);
//             store(fri2, frbeg+i2);
//             store(fri3, frbeg+i3);
//             store(fii0, fibeg+i0);
//             store(fii1, fibeg+i1);
//             store(fii2, fibeg+i2);
//             store(fii3, fibeg+i3);
//           }
//         };
//         eve::algo::for_each[eve::algo::expensive_callable](view, doit);
//       }
//       else
//       {
//        std::cout << "scalar" << std::endl;
        using c_t =  eve::complex<T>;
        for (i_t j=0; j<m4; ++j, ph+= ph0)
        {
          auto cs  = exp_ipi(ph);
          auto cs2 = sqr(cs);
          auto cs3 = cs2*cs;

          for (i_t r=0; r<n; r+=m)
          {
            i_t i0 = j + r;
            i_t i1 = i0 + m4;
            i_t i2 = i1 + m4;
            i_t i3 = i2 + m4;
            auto bfri0 = *(fr.begin()+i0);
            auto bfri1 = *(fr.begin()+i1);
            auto bfri2 = *(fr.begin()+i2);
            auto bfri3 = *(fr.begin()+i3);
            auto bfii0 = *(fi.begin()+i0);
            auto bfii1 = *(fi.begin()+i1);
            auto bfii2 = *(fi.begin()+i2);
            auto bfii3 = *(fi.begin()+i3);
            double xr, yr, ur, vr, xi, yi, ui, vi;

            // {x, u} = {f[i0]+f[i2], f[i0]-f[i2]}:
            sumdiff(bfri0, bfri2, xr, ur);
            sumdiff(bfii0, bfii2, xi, ui);

            // {y, v} = {f[i1]+f[i3], (f[i1]-f[i3])*(0,is)}:
            sumdiff(bfii3, bfii1, yi, vr);
            sumdiff(bfri1, bfri3, yr, vi);

            diffsum3(xr, yr, bfri0);
            diffsum3(xi, yi, bfii0);

            //cmult(c2, s2, yr, yi, bfri1, bfii1);
            std::tie(bfri1, bfii1) = cs2*c_t(yr, yi);
            sumdiff(ur, vr, xr, yr);
            sumdiff(ui, vi, xi, yi);

            //cmult(c3, s3, yr, yi, bfri3, bfii3);
            std::tie(bfri3, bfii3) = cs3*c_t(yr, yi);

            //cmult(c,  s,  xr, xi, bfri2, bfii2);
            std::tie(bfri2, bfii2) = cs*c_t(xr, xi);
          }
        }
//      }
    }
    if ( (ldn&1)!=0 )  // n is not a power of 4, need a radix-8 step
    {
      // for (i_t i0=0; i0<n; i0+=8)  fft8_dif_core_p1(fr+i0, fi+i0);
      std::cout << "notdone" << std::endl;
      exit(1);
    }
    else
    {
      for (i_t i0=0; i0<n; i0+=4)
      {
        T xr, yr, ur, vr, xi, yi, ui, vi;
        ulong i1 = i0 + 1;
        ulong i2 = i1 + 1;
        ulong i3 = i2 + 1;
        auto bfri0 = *(fr.begin()+i0);
        auto bfri1 = *(fr.begin()+i1);
        auto bfri2 = *(fr.begin()+i2);
        auto bfri3 = *(fr.begin()+i3);
        auto bfii0 = *(fi.begin()+i0);
        auto bfii1 = *(fi.begin()+i1);
        auto bfii2 = *(fi.begin()+i2);
        auto bfii3 = *(fi.begin()+i3);

        sumdiff(bfri0, bfri2, xr, ur);
        sumdiff(bfri1, bfri3, yr, vi);
        sumdiff(bfii0, bfii2, xi, ui);
        sumdiff(bfii3, bfii1, yi, vr);

        sumdiff(xi, yi, bfii0, bfii1);
        sumdiff(ui, vi, bfii2, bfii3);
        sumdiff(xr, yr, bfri0, bfri1);
        sumdiff(ur, vr, bfri2, bfri3);
      }
    }
    scaleit(fr, fi, fac);
//     if (fac != T(1))
//     {
//       for(size_t i=0; i < n; ++i)
//       {
//         *(frbeg+i) *= fac;
//         *(fibeg+i) *= fac;
//       }
//     }
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_dif4_(EVE_SUPPORTS(cpu_), aos_type const &
              , R &f
              , T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto n =  f.size();
    using i_t =  decltype(n);
    using c_t = eve::complex<T>;
    std::vector<T> fr(n),  fi(n);
    auto b = f.begin();
    for(i_t i=0; i < n; ++i)
    {
      auto z = *(b+i);
      fr[i] = real(z);
      fi[i] = imag(z);
    }
    aos(fft_dif4)(fr, fi, fac);
    for(i_t i=0; i < n; ++i)
    {
      *(b+i) = c_t(fr[i], fi[i]);
    }
  }


//    i_t ldm = (ldn&1);
 //    if ( ldm!=0 )  // n is not a power of 4, need a radix-8 step
//     {
//       std::cout << "exit" << std::endl;
//       exit(1); // pas fait
//       //for (i_t i0=0; i0<n; i0+=8)  fft8_dit_core_p1(fr+i0, fi+i0);
//     }
//     else
//     {
//      for (i_t i0=0; i0<n; i0+=4)
//       {
//         double xr, yr, ur, vr, xi, yi, ui, vi;
//         i_t i1 = i0 + 1;
//         i_t i2 = i1 + 1;
//         i_t i3 = i2 + 1;

//         auto bfri0 = *(fr.begin()+i0);
//         auto bfri1 = *(fr.begin()+i1);
//         auto bfri2 = *(fr.begin()+i2);
//         auto bfri3 = *(fr.begin()+i3);
//         auto bfii0 = *(fi.begin()+i0);
//         auto bfii1 = *(fi.begin()+i1);
//         auto bfii2 = *(fi.begin()+i2);
//         auto bfii3 = *(fi.begin()+i3);
//         sumdiffb(bfri0, bfri1, xr, ur);
//         sumdiffb(bfri2, bfri3, yr, vi);
//         sumdiffb(bfii0, bfii1, xi, ui);
//         sumdiffb(bfii3, bfii2, yi, vr);

//         sumdiffb(ui, vi, bfii1, bfii3);
//         sumdiffb(xi, yi, bfii0, bfii2);
//         sumdiffb(ur, vr, bfri1, bfri3);
//         sumdiffb(xr, yr, bfri0, bfri2);
//       }
// //      pr1("ensuite frbeg ", frbeg);
//     }


//   template<range R, floating_scalar_value T>
//   EVE_FORCEINLINE  void
//   fft_dif4_(EVE_SUPPORTS(cpu_), soa_type const &
//               , R &f
//               , T fac) noexcept
//   requires(eve::is_complex_v<typename R::value_type>)
//   {
//     auto n =  f.size();
// //    using i_t =  decltype(n);
// //    using c_t = eve::complex<T>;
// //    std::vector<T> fr(n),  fi(n);
//     auto b = f.begin().base;
//     auto [bfr, bfi] = b;
//     auto fr = eve::algo::as_range(bfr, bfr+n);
//     auto fi = eve::algo::as_range(bfi, bfi+n);
//     aos(fft_dif4)(fr, fi, fac);
// //    f =  algo::views::zip(as_range(bfr, bfr+n), as_range(bfi, bfi+n));
//   }

}
