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
//    std::cout << "icitte" << std::endl;
    using c_t = eve::complex<T>;
    auto n =  fr.size();
    using i_t = decltype(n);
    i_t lx = 2;
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    auto ldn = eve::countr_zero(n); //eve::log2(n));

//     auto pr = [](auto name, auto v){
//       std::cout << name << " = (";
//       for(size_t i=0; i < v.size() ; ++i) std::cout <<v[i] << " ";
//       std::cout << ")\n";
//     };
    // pr("fr ", fr);
    // pr("fi ", fi);
    auto frbeg = fr.begin();
    auto fibeg = fi.begin();
    if ( n<=2 )
    {
      if ( n==2 )
      {
        sd(*frbeg, *(frbeg+1));
        sd(*fibeg, *(fibeg+1));
      }
      return;
    }
    i_t lx2 = lx << 1;
//    std::cout << "ldn " << ldn << std::endl;
//     std::cout << "lx2 " << lx2 << std::endl;
//     std::cout << "lx  " << lx << std::endl;

    for (i_t ldm=ldn; ldm >= lx2; ldm-=lx)
    {
//      std::cout << "ldm" << ldm << std::endl;
      i_t m = (1UL<<ldm);
      i_t m4 = (m>>lx);
      auto ph = T(0);
      const auto ph0 = 2*rec(T(m));

//       if(m4 < eve::nofs_cardinal_v<T>)
//       {
//      using c_t =  eve::complex<T>;
//        std::cout << "m4 " << m4 << std::endl;
      for (i_t j=0; j<m4; ++j)
      {
        auto cs  = exp_ipi(ph);
        ph+= ph0;
        auto cs2 = sqr(cs);
        auto cs3 = cs2*cs;
//          std::cout << "n" << n << std::endl;
//          std::cout << "cs " << cs << "  " << cs2 <<  "   " << cs3 << std::endl;
        for (i_t r=0; r<n; r+=m)
        {
//           std::cout << "r" << r << std::endl;
          i_t i0 = j + r;
          i_t i1 = i0 + m4;
          i_t i2 = i1 + m4;
          i_t i3 = i2 + m4;
          auto bfri0 = (frbeg+i0);
          auto bfri1 = (frbeg+i1);
          auto bfri2 = (frbeg+i2);
          auto bfri3 = (frbeg+i3);

          auto bfii0 = (fibeg+i0);
          auto bfii1 = (fibeg+i1);
          auto bfii2 = (fibeg+i2);
          auto bfii3 = (fibeg+i3);
//           {
//             auto a0 = c_t(*bfri0, *bfii0);
//             auto a1 = c_t(*bfri1, *bfii1);
//             auto a2 = c_t(*bfri2, *bfii2);
//             auto a3 = c_t(*bfri3, *bfii3);

//             auto t0 = (a0+a2) + (a1+a3);
//             auto t2 = (a0+a2) - (a1+a3);

//             auto t1 = (a0-a2) + eve::i(as<T>())*(a1-a3);
//             auto t3 = (a0-a2) - eve::i(as<T>())*(a1-a3);

//             t1 *= cs;
//             t2 *= cs2;
//             t3 *= cs3;

//             std::cout << t0 << "   " << t2 << "   " << t1 << "   " << t3 << std::endl;
//             *bfri0 = real(t0);
//             *bfii0 = imag(t0);
//             *bfri1 = real(t2);
//             *bfii1 = imag(t2);
//             *bfri2 = real(t1);
//             *bfii2 = imag(t1);
//             *bfri3 = real(t3);
//             *bfii3 = imag(t3);
//           }

          T xr, yr, ur, vr, xi, yi, ui, vi;
//           auto  sumdiff = [](auto a, auto b, auto &s, auto &d)// {s, d}  <--| {a+b, a-b}
//             { s=a+b; d=a-b; };
//           auto diffsum3 = [](auto a, auto &b, auto &s)
//             { s=a+b; b=a-b; };
//           auto cmult = [](auto c, auto s,
//                           auto x, auto y,
//                           auto &u, auto &v)
//             {
//               u = x * c - y * s;
//               v = y * c + x * s;
//             };

          // {x, u} = {f[i0]+f[i2], f[i0]-f[i2]}:
          sd(*bfri0, *bfri2, xr, ur);
          sd(*bfii0, *bfii2, xi, ui);

          // {y, v} = {f[i1]+f[i3], (f[i1]-f[i3])*(0,is)}:
          sd(*bfii3, *bfii1, yi, vr);
          sd(*bfri1, *bfri3, yr, vi);

          ds(xr, yr, *bfri0);
          ds(xi, yi, *bfii0);

          //cmult(c2, s2, yr, yi, bfri1, bfii1);
//          cmult(real(cs2), imag(cs2), yr, yi, *bfri1, *bfii1);
          {auto [rr, ii] =  cs2*c_t(yr, yi); *bfri1 = rr; *bfii1 = ii;}


          sd(ur, vr, xr, yr);
          sd(ui, vi, xi, yi);

          //cmult(c3, s3, yr, yi, bfri3, bfii3);
          {auto [rr, ii] =  cs3*c_t(yr, yi); *bfri3 = rr; *bfii3 = ii;}
//          cmult(real(cs3), imag(cs3), yr, yi, *bfri3, *bfii3);
          // std::tie(bfri3, bfii3) = cs3*c_t(yr, yi);

          {auto [rr, ii] =  cs*c_t(xr, xi); *bfri2 = rr; *bfii2 = ii;}
          //  cmult(real(cs), imag(cs), xr, xi, *bfri2, *bfii2);
          //  cmult(c,  s,  xr, xi, bfri2, bfii2);
          //           std::tie(bfri2, bfii2) = cs*c_t(xr, xi);
//          std::swap(*bfri3, *bfri2);

//           std::cout << *bfri0 << ", " << *bfii0
//                     << "    " << *bfri1 << ", " << *bfii1
//                     << "    " << *bfri2 << ", " << *bfii2
//                     << "    " << *bfri3 << ", " << *bfii3 << std::endl;
        }
      }

    }
//           pr("loop fr", fr);
//           pr("loop fi", fi);
//      }

    if ( (ldn&1)!=0 )  // n is not a power of 4, need a radix-8 step
    {
      // for (i_t i0=0; i0<n; i0+=8)  fft8_dif_core_p1(fr+i0, fi+i0);
      auto fft8_dif_core_p1 = [](auto frb, auto fib){
        // 8-point decimation in frequency FFT
        const T invsqrt2 = invsqrt_2(as<T>());
        // INPUT_RE:
        auto t1r = *(frb+0) + *(frb+4);
        auto t2r = *(frb+2) + *(frb+6);
        auto t7r = t1r + t2r;
        auto t3r = *(frb+1) - *(frb+5);
        auto t4r = *(frb+1) + *(frb+5);
        auto t5r = *(frb+3) + *(frb+7);
        auto t8r = t4r + t5r;
        auto t6r = *(frb+3) - *(frb+7);

        auto m0r = t7r + t8r;
        auto m1r = t7r - t8r;
        auto m2r = t1r - t2r;
        auto m3r = *(frb+0) - *(frb+4);
        auto m4r = invsqrt2 * (t3r - t6r);



#define m5i t6r
#define m6i t7r
#define m7i t8r
        t8r =  -(invsqrt2 * (t3r + t6r));
        t6r = t5r - t4r;
        t7r = *(frb+6) - *(frb+2);

        // INPUT_IM:
        auto t1i = *(fib+0) + *(fib+4);
        auto t2i = *(fib+2) + *(fib+6);
        auto t7i = t1i + t2i;
        auto t3i = *(fib+1) - *(fib+5);
        auto t4i = *(fib+1) + *(fib+5);
        auto t5i = *(fib+3) + *(fib+7);
        auto t8i = t4i + t5i;
        auto t6i = *(fib+3) - *(fib+7);

        auto m0i = t7i + t8i;
        auto m1i = t7i - t8i;
        auto m2i = t1i - t2i;
        auto m3i = *(fib+0) - *(fib+4);
        auto m4i = invsqrt2 * (t3i - t6i);

#define m5r t6i
#define t7i t7i
#define m7r t8i
        t8i = invsqrt2 * (t3i + t6i);
        t6i = t4i - t5i;
        t7i = *(fib+2) - *(fib+6);
        t1r = m3r + m4r;
        t2r = m3r - m4r;
        t3r = t7i + t8i;
        t4r = t7i - t8i;

        // OUTPUT_RE:
        *(frb+0) = m0r;
        *(frb+7) = t1r + t3r;
        *(frb+3) = m2r + t6i;
        *(frb+5) = t2r - t4r;
        *(frb+1) = m1r;
        *(frb+6) = t2r + t4r;
        *(frb+2) = m2r - t6i;
        *(frb+4) = t1r - t3r;
        t1r = m3i + m4i;
        t2r = m3i - m4i;
        t3r = t7r + t8r;
        t4r = t7r - t8r;

        // OUTPUT_IM:
        *(fib+0) = m0i;
        *(fib+7) = t1r + t3r;
        *(fib+3) = m2i + t6r;
        *(fib+5) = t2r - t4r;
        *(fib+1) = m1i;
        *(fib+6) = t2r + t4r;
        *(fib+2) = m2i - t6r;
        *(fib+4) = t1r - t3r;
      };
      for (i_t i0=0; i0<n; i0+=8){
        fft8_dif_core_p1(frbeg+i0, fibeg+i0);
      }
    }
    else
    {
//      std::cout << "n " << n << std::endl;
      for (i_t i0=0; i0<n; i0+=4)
      {
        T xr, yr, ur, vr, xi, yi, ui, vi;
        ulong i1 = i0 + 1;
        ulong i2 = i1 + 1;
        ulong i3 = i2 + 1;
        auto bfri0 = (frbeg+i0);
        auto bfri1 = (frbeg+i1);
        auto bfri2 = (frbeg+i2);
        auto bfri3 = (frbeg+i3);
        auto bfii0 = (fibeg+i0);
        auto bfii1 = (fibeg+i1);
        auto bfii2 = (fibeg+i2);
        auto bfii3 = (fibeg+i3);

        sd(*bfri0, *bfri2, xr, ur);
        sd(*bfri1, *bfri3, yr, vi);
        sd(*bfii0, *bfii2, xi, ui);
        sd(*bfii3, *bfii1, yi, vr);

        sd(xi, yi, *bfii0, *bfii1);
        sd(ui, vi, *bfii2, *bfii3);
        sd(xr, yr, *bfri0, *bfri1);
        sd(ur, vr, *bfri2, *bfri3);
      }
    }
    // pr("fr", fr);
    // pr("fi", fi);
    scaleit(fr, fi, fac);
//     if (fac != T(1))
//     {
//       for(size_t i=0; i < n; ++i)
//       {
//         *(frbeg+i) *= fac;
//         *(fibeg+i) *= fac;
//       }
//     }
    aos(revbin_permute)(fr);
    aos(revbin_permute)(fi);
    // pr("fr", fr);
    // pr("fi", fi);

  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_dif4_(EVE_SUPPORTS(cpu_), aos_type const &
              , R &f
              , T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
//     auto pr = [](auto name, auto v){
//       std::cout << name << " = (";
//       for(size_t i=0; i < v.size() ; ++i) std::cout << v[i] << " ";
//       std::cout << ")\n";
//    };
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
    // pr("fr", fr);
    // pr("fi", fi);
//    std::cout << "aos" << std::endl;
    aos(fft_dif4)(fr, fi, fac);
    // pr("ap fr", fr);
    // pr("ap fi", fi);
//    std::cout << "aos" << std::endl;
    for(i_t i=0; i < n; ++i)
    {
      *(b+i) = c_t(fr[i], fi[i]);
//      std::cout <<  *(b+i) << std::endl;
    }
  }



  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_dif4_(EVE_SUPPORTS(cpu_), soa_type const &
              , R &f
              , T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto [fr, fi] = soac2ri(f);
    aos(fft_dif4)(fr, fi, fac);
  }
}




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
