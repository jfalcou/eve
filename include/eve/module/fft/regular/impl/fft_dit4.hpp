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
  fft_dit4_(EVE_SUPPORTS(cpu_), aos_type const &
              , R & fr
              , R & fi
              , T fac) noexcept
  //  requires(eve::is_complex_v<typename R::value_type>)
  {

    [[maybe_unused]] auto pr = [](auto name, auto v){
      std::cout << name << " = (";
      for(size_t i=0; i < v.size() ; ++i) std::cout << *(v.begin()+i) << " ";
      std::cout << ")\n";
    };
//     pr("fr ", fr);
//     pr("fi ", fi);
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
    auto  cmult = [](auto c, auto s,
                     auto x, auto y,
                     auto &u, auto &v){
      // {u,v} <--| {x*c-y*s, x*s+y*c}
      // used in generated complex fhts
      u = x * c - y * s;
      v = y * c + x * s;
    };
    auto sumdiff3_r = [](auto &a, auto b, auto &d){
      // {a,b,d} <--| {a+b, b, b-a}  (used in split-radix FFTs)
      // NEVER call like func(a,b,a) or func(a,b,b)
      d=b-a; a+=b;
    };

//     auto pr1 = [n](auto name, auto pr){
//       std::cout << name << " = (";
//       for(size_t i=0; i < n ; ++i) std::cout << *(pr+i) << " ";
//       std::cout << ")\n";
//     };

    auto frbeg = fr.data();
    auto fibeg = fi.data();
//     pr1("frbeg ", frbeg);
//     pr1("fibeg ", fibeg);
//     auto z =  load(frbeg);
//     std::cout << "z " << z << std::endl;
    if ( n<=2 )
    {
      if ( n==2 )
      {
        sumdiff(*frbeg, *(frbeg+1));
        sumdiff(*fibeg, *(fibeg+1));
      }
      return;
    }
    i_t ldm = (ldn&1);
//     std::cout << "ldm " << ldm << std::endl;
//     std::cout << "ldn " << ldn << std::endl;
    if ( ldm!=0 )  // n is not a power of 4, need a radix-8 step
    {
      auto fft8_dit_core_p1 = [](auto frb, auto fib){
        // 8-point decimation in time FFT
        const T invsqrt2 = invsqrt_2(as<T>());
        // INPUT_RE:
        T t1r = *(frb+0) + *(frb+1);
        T t2r = *(frb+2) + *(frb+3);
        T t7r = t1r + t2r;
        T t3r = *(frb+4) - *(frb+5);
        T t4r = *(frb+4) + *(frb+5);
        T t5r = *(frb+6) + *(frb+7);
        T t8r = t4r + t5r;
        T t6r = *(frb+6) - *(frb+7);

        T m0r = t7r + t8r;
        T m1r = t7r - t8r;
        T m2r = t1r - t2r;
        T m3r = *(frb+0) - *(frb+1);
        T m4r = invsqrt2 * (t3r - t6r);

        t8r = invsqrt2 * (t3r + t6r);
        t6r = t5r - t4r;
        t7r = *(frb+3) - *(frb+2);

        // INPUT_IM:
        T t1i = *(fib+0) + *(fib+1);
        T t2i = *(fib+2) + *(fib+3);
        T t7i = t1i + t2i;
        T t3i = *(fib+4) - *(fib+5);
        T t4i = *(fib+4) + *(fib+5);
        T t5i = *(fib+6) + *(fib+7);
        T t8i = t4i + t5i;
        T t6i = *(fib+6) - *(fib+7);

        T m0i = t7i + t8i;
        T m1i = t7i - t8i;
        T m2i = t1i - t2i;
        T m3i = *(fib+0) - *(fib+1);
        T m4i = invsqrt2 * (t3i - t6i);

        t8i = invsqrt2 * (t3i + t6i);
        t6i = t4i - t5i;
        t7i = *(fib+2) - *(fib+3);

        t1r = m3r + m4r;
        t2r = m3r - m4r;
        t3r = t7i + t8i;
        t4r = t7i - t8i;

        // OUTPUT_RE:
        *(frb+0) = m0r;
        *(frb+7) = t1r + t3r;
        *(frb+6) = m2r + t6i;
        *(frb+5) = t2r - t4r;
        *(frb+4) = m1r;
        *(frb+3) = t2r + t4r;
        *(frb+2) = m2r - t6i;
        *(frb+1) = t1r - t3r;

        t1r = m3i + m4i;
        t2r = m3i - m4i;
        t3r = t7r - t8r;
        t4r = t7r + t8r;

        // OUTPUT_IM:
        *(fib+0) = m0i;
        *(fib+7) = t1r + t3r;
        *(fib+6) = m2i + t6r;
        *(fib+5) = t2r - t4r;
        *(fib+4) = m1i;
        *(fib+3) = t2r + t4r;
        *(fib+2) = m2i - t6r;
        *(fib+1) = t1r - t3r;
      };

      for (i_t i0=0; i0<n; i0+=8){
         fft8_dit_core_p1(frbeg+i0, fibeg+i0);
      }
    }
    else
    {
      for (i_t i0=0; i0<n; i0+=4)
      {
        T xr, yr, ur, vr, xi, yi, ui, vi;
        i_t i1 = i0 + 1;
        i_t i2 = i1 + 1;
        i_t i3 = i2 + 1;

        sumdiffb(*(fr.begin()+i0), *(fr.begin()+i1), xr, ur);
        sumdiffb(*(fr.begin()+i2), *(fr.begin()+i3), yr, vi);
        sumdiffb(*(fi.begin()+i0), *(fi.begin()+i1), xi, ui);
        sumdiffb(*(fi.begin()+i3), *(fi.begin()+i2), yi, vr);

        sumdiffb(ui, vi, *(fi.begin()+i1), *(fi.begin()+i3));
        sumdiffb(xi, yi, *(fi.begin()+i0), *(fi.begin()+i2));
        sumdiffb(ur, vr, *(fr.begin()+i1), *(fr.begin()+i3));
        sumdiffb(xr, yr, *(fr.begin()+i0), *(fr.begin()+i2));
      }
//      pr1("ensuite frbeg ", frbeg);
    }
    ldm += 2*lx;
    for ( ; ldm<=ldn; ldm+=lx)
    {
      i_t m = (1UL<<ldm);
      i_t m4 = (m>>lx);
//       std::cout << "m =  " << m << " m4 "<< m4 << std::endl;
      const auto ph0 = T(2)/m;

      if(m4 >= eve::nofs_cardinal_v<T>)
      {
//         std::cout << "simd" << std::endl;
//         pr("scrav fr", fr);
//         pr("scrav fi", fi);

//         std::cout << "m4 " << m4 << std::endl;
        auto js = eve::views::iota(T{0}, m4);
        auto phs= eve::views::iota_with_step(T{0}, ph0, m4);
        auto view = eve::views::zip(js, phs);
//        int brk = 0;
        auto doit = [/*&brk, */n, m, m4, &fr, &fi, sumdiff, sumdiff3_r, cmult, sumdiffb](auto zz, auto ignore){
//           if (brk == 2) return;
//           ++brk;
          auto [j, ph] = load[ignore](zz);
//          std::cout << "j  " << j << std::endl;
//          std::cout << "ph " << ph<< std::endl;
          auto cs  = exp_ipi(ph);
//          std::cout << "cs " << cs<< std::endl;
          using c_t =  decltype(cs);
          auto cs2 = sqr(cs);
//          std::cout << "cs2 " << cs2<< std::endl;
          auto cs3 = cs2*cs;
//          std::cout << "cs3 " << cs3<< std::endl;
          auto [c, s] = cs;
          auto [c3, s3] = cs3;
          for (i_t r=0; r<n; r+=m)
          {
            i_t i0 = j.get(0) + r;
            i_t i1 = i0 + m4;
            i_t i2 = i1 + m4;
            i_t i3 = i2 + m4;
//           std::cout << " i0 = " << i0 << ", i1 = " << i1
//                     << ", i2 = " << i2 << ", i3 = " << i3 << std::endl;
            auto frbeg = fr.data();
            auto fibeg = fi.data();
            auto fri0 = load(frbeg+i0);
            auto fri1 = load(frbeg+i1);
            auto fri2 = load(frbeg+i2);
            auto fri3 = load(frbeg+i3);
            auto fii0 = load(fibeg+i0);
            auto fii1 = load(fibeg+i1);
            auto fii2 = load(fibeg+i2);
            auto fii3 = load(fibeg+i3);
            auto tmp = cs2*c_t(fri1, fii1);
//             std::cout << "fri0 " << fri0 << std::endl;
//             std::cout << "fri1 " << fri1 << std::endl;
//             std::cout << "fri2 " << fri2 << std::endl;
//             std::cout << "fri3 " << fri3 << std::endl;

            auto xr = real(tmp);
            auto xi = imag(tmp);
            //         [xr, xi] = cs2*c_t(fri1, fii1);
            using wT_t = decltype(xr);
            wT_t ur, ui;
            sumdiff3_r(xr, fri0, ur);
            sumdiff3_r(xi, fii0, ui);
//             std::cout << "xr " << xr << std::endl;
//             std::cout << "xi " << xi << std::endl;
            wT_t yr, vr, vi, yi;
            cmult(c,  s,  fri2, fii2, yr, vr);
            cmult(c3, s3, fri3, fii3, vi, yi);

            sumdiff(yr, vi);
            sumdiff(yi, vr);

//             std::cout << "yr " << yr << std::endl;
//             std::cout << "vr " << vr << std::endl;
//             std::cout << "vi " << vi << std::endl;
//             std::cout << "yi " << yi << std::endl;
            sumdiffb(ur, vr, fri1, fri3);
            sumdiffb(ui, vi, fii1, fii3);
            sumdiffb(xr, yr, fri0, fri2);
            sumdiffb(xi, yi, fii0, fii2);
//            std::cout << "ap fri0 " << fri0 << std::endl;
//            std::cout << "ap fri1 " << fri1 << std::endl;
//           std::cout << "ap fri2 " << fri2 << std::endl;
//            std::cout << "ap fri3 " << fri3 << std::endl;
            store(fri0, frbeg+i0);
            store(fri1, frbeg+i1);
            store(fri2, frbeg+i2);
            store(fri3, frbeg+i3);
            store(fii0, fibeg+i0);
            store(fii1, fibeg+i1);
            store(fii2, fibeg+i2);
            store(fii3, fibeg+i3);
          }
        };
        eve::algo::for_each[eve::algo::expensive_callable](view, doit);
//         pr("simd ap fr", fr);
//         pr("simd ap fi", fi);
      }
      else
      {
//        std::cout << "scalar" << std::endl;
//         pr("av fr", fr);
//         pr("av fi", fi);
        T ph(0);
        using c_t =  eve::complex<T>;
        //       int brk = 0;
        for (i_t j=0; j<m4; j++)
        {
//          if (brk == 8) break;
//          ++brk;
          auto cs  = exp_ipi(ph);
//         std::cout << "j " << j;
//         std::cout << " phi " << ph;
//         std::cout << " cs  " << cs << std::endl;
          ph += ph0;
          auto cs2 = sqr(cs);
          auto cs3 = cs2*cs;
          auto [c, s] = cs;
//        std::cout << "cs " << cs << " c " << c << " s " << s << std::endl;
          auto [c3, s3] = cs3;

          for (i_t r=0; r<n; r+=m)
          {
            i_t i0 = j + r;
            i_t i1 = i0 + m4;
            i_t i2 = i1 + m4;
            i_t i3 = i2 + m4;
//           std::cout << "->i0 = " << i0 << ", i1 = " << i1 <<
//             ", i2 = " << i2 << ", i3 = " << i3 << std::endl;
//           std::cout << "fri0 " << fr[i0] << std::endl;
//           std::cout << "fri1 " << fr[i1] << std::endl;
//           std::cout << "fri2 " << fr[i2] << std::endl;
//           std::cout << "fri3 " << fr[i3] << std::endl;

            //           cmult(c2, s2, fr[i1], fi[i1], xr, xi);
            auto [xr, xi] = cs2*c_t(*(fr.begin()+i1), *(fi.begin()+i1));
            T ur, ui;
            sumdiff3_r(xr, *(fr.begin()+i0), ur);
            sumdiff3_r(xi, *(fi.begin()+i0), ui);
//             std::cout << "xr " << xr << std::endl;
//             std::cout << "xi " << xi << std::endl;
            T yr, vr, vi, yi;
            cmult(c,  s,  *(fr.begin()+i2), *(fi.begin()+i2), yr, vr);
            cmult(c3, s3, *(fr.begin()+i3), *(fi.begin()+i3), vi, yi);

            sumdiff(yr, vi);
            sumdiff(yi, vr);
//                       std::cout << "yr " << yr << std::endl;
//                       std::cout << "vr " << vr << std::endl;
//             std::cout << "vi " << vi << std::endl;
//             std::cout << "yi " << yi << std::endl;

            sumdiffb(ur, vr, *(fr.begin()+i1), *(fr.begin()+i3));
            sumdiffb(ui, vi, *(fi.begin()+i1), *(fi.begin()+i3));
            sumdiffb(xr, yr, *(fr.begin()+i0), *(fr.begin()+i2));
            sumdiffb(xi, yi, *(fi.begin()+i0), *(fi.begin()+i2));
//           std::cout << "ap fri0 " << fr[i0] << std::endl;
//            std::cout << "ap fri1 " << fr[i1] << std::endl;
//            std::cout << "ap fri2 " << fr[i2] << std::endl;
//           std::cout << "ap fri3 " << fr[i3] << std::endl;
          }
        }
//         pr("scal ap fr", fr);
//         pr("scal ap fi", fi);
        // return;
      }
    }
    if (fac != T(1))
    {
      for(size_t i=0; i < n; ++i)
      {
        *(frbeg+i) *= fac;
        *(fibeg+i) *= fac;
      }
    }

  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_dit4_(EVE_SUPPORTS(cpu_), aos_type const &
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
    aos(fft_dit4)(fr, fi, fac);
    for(i_t i=0; i < n; ++i)
    {
      *(b+i) = c_t(fr[i], fi[i]);
    }
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_dit4_(EVE_SUPPORTS(cpu_), soa_type const &
           , R &f
           , T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto n =  f.size();
    auto [bfr, bfi] = f.begin().base;
    auto fr = eve::algo::as_range(bfr, bfr+n);
    auto fi = eve::algo::as_range(bfi, bfi+n);
    aos(fft_dit4)(fr, fi, fac);
  }

}
