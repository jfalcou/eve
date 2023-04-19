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
    auto frbeg = fr.data();
    auto fibeg = fi.data();
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
    for (i_t ldm=ldn; ldm >= lx2; ldm-=lx)
    {
      i_t m = (1UL<<ldm);
      i_t m4 = (m>>lx);
      auto ph = T(0);
      const auto ph0 = 2*rec(T(m));

      if(m4 > eve::nofs_cardinal_v<T>)
      {
        auto js = eve::views::iota(T{0}, m4);
        auto phs= eve::views::iota_with_step(T{0}, ph0, m4);
        auto view = eve::views::zip(js, phs);
        auto doit = [n, m, m4, frbeg, fibeg](auto zz, auto ignore){
          auto [j, ph] = load[ignore](zz);
          auto cs  = exp_ipi(ph);
          auto cs2 = sqr(cs);
          auto cs3 = cs2*cs;
          for (i_t r=0; r<n; r+=m)
          {
            i_t i0 = j.get(0) + r;
            i_t i1 = i0 + m4;
            i_t i2 = i1 + m4;
            i_t i3 = i2 + m4;
            auto fri0 = load(frbeg+i0);
            auto fri1 = load(frbeg+i1);
            auto fri2 = load(frbeg+i2);
            auto fri3 = load(frbeg+i3);
            auto fii0 = load(fibeg+i0);
            auto fii1 = load(fibeg+i1);
            auto fii2 = load(fibeg+i2);
            auto fii3 = load(fibeg+i3);
            using wT_t = eve::wide<T, fixed<nofs_cardinal_v<T>>>;
//            using wC_t = eve::as_complex<wT_t>;
            wT_t xr, yr, ur, vr, xi, yi, ui, vi;
            sd(fri0, fri2, xr, ur);
            sd(fii0, fii2, xi, ui);
            sd(fii3, fii1, yi, vr);
            sd(fri1, fri3, yr, vi);
            ds(xr, yr, fri0);
            ds(xi, yi, fii0);
            { auto [rr, ii] =  cs2*eve::as_complex_t<wT_t>{yr, yi}; fri1 = rr; fii1 = ii;}
            sd(ur, vr, xr, yr);
            sd(ui, vi, xi, yi);
            {auto [rr, ii] = cs3*eve::as_complex_t<wT_t>{yr, yi}; fri3 = rr; fii3 = ii;}
            {auto [rr, ii] = cs* eve::as_complex_t<wT_t>{xr, xi}; fri2 = rr; fii2 = ii;}
            store(fri0, frbeg+i0);
            store(fri1, frbeg+i1);
            store(fri2, frbeg+i2);
            store(fri3, frbeg+i3);
            store(fii0, fibeg+i0);
            store(fii1, fibeg+i1);
            store(fii2, fibeg+i2);
            store(fii3, fibeg+i3);          }
        };
        eve::algo::for_each[eve::algo::expensive_callable](view, doit);
      }
      else
      {
        for (i_t j=0; j<m4; ++j)
        {
          auto cs  = exp_ipi(ph);
          ph+= ph0;
          auto cs2 = sqr(cs);
          auto cs3 = cs2*cs;
          for (i_t r=0; r<n; r+=m)
          {
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
            T xr, yr, ur, vr, xi, yi, ui, vi;

            sd(*bfri0, *bfri2, xr, ur);
            sd(*bfii0, *bfii2, xi, ui);
            sd(*bfii3, *bfii1, yi, vr);
            sd(*bfri1, *bfri3, yr, vi);
            ds(xr, yr, *bfri0);
            ds(xi, yi, *bfii0);
            {auto [rr, ii] =  cs2*c_t(yr, yi); *bfri1 = rr; *bfii1 = ii;}
            sd(ur, vr, xr, yr);
            sd(ui, vi, xi, yi);
            {auto [rr, ii] = cs3*c_t(yr, yi); *bfri3 = rr; *bfii3 = ii;}
            {auto [rr, ii] = cs*c_t(xr, xi); *bfri2 = rr; *bfii2 = ii;}
          }
        }
      }
    }
    if ( (ldn&1)!=0 )  // n is not a power of 4, need a radix-8 step
    {
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
    scaleit(fr, fi, fac);
    aos(revbin_permute)(fr);
    aos(revbin_permute)(fi);
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
