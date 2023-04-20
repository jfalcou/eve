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
#include <eve/pattern.hpp>

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
  {

    [[maybe_unused]] auto pr = [](auto name, auto v){
      std::cout << name << " = (";
      for(size_t i=0; i < v.size() ; ++i) std::cout << *(v.begin()+i) << " ";
      std::cout << ")\n";
    };
    aos(revbin_permute)(fr, fi);
    auto n =  fr.size();
    using i_t = decltype(n);
    i_t lx = 2;
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    auto ldn = eve::countr_zero(n); //eve::log2(n));

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
    i_t ldm = (ldn&1);
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
        if constexpr(eve::nofs_cardinal_v<T> >= 8)
        {
          using w_t = wide<T, fixed<4>>;
          auto fr0 = load(fr.data()+i0, as<w_t>());
          auto fi0 = load(fi.data()+i0, as<w_t>());
          auto z = eve::combine(fr0, fi0);
          auto xryrxiyi = eve::shuffle(z, eve::pattern<0, 2, 4+0, 4+3>);
          auto urviuivr = eve::shuffle(z, eve::pattern<1, 3, 4+1, 4+2>);
          w_t a, b;
          sd(xryrxiyi, urviuivr, a, b);
          z = eve::combine(a, b);
          auto uixiurxr = eve::shuffle(z, eve::pattern<4+2, 2, 4+0, 0>);
          auto viyivryr = eve::shuffle(z, eve::pattern<4+1, 3, 4+3, 1>);
          w_t  ii1_ii0_ri1_ri0, ii3_ii2_ri3_ri2;
          sd(uixiurxr, viyivryr, ii1_ii0_ri1_ri0, ii3_ii2_ri3_ri2);
          z = eve::combine(ii1_ii0_ri1_ri0, ii3_ii2_ri3_ri2);
          auto rr = eve::shuffle(z, eve::pattern<3, 2, 4+3, 4+2>);
          auto ii = eve::shuffle(z, eve::pattern<1, 0, 4+1, 4+0>);
          store(rr, fr.data()+i0);
          store(ii, fi.data()+i0);
        }
        else
        {
          T xr, yr, ur, vr, xi, yi, ui, vi;
          i_t i1 = i0 + 1;
          i_t i2 = i1 + 1;
          i_t i3 = i2 + 1;
          sd(*(fr.begin()+i0), *(fr.begin()+i1), xr, ur);
          sd(*(fr.begin()+i2), *(fr.begin()+i3), yr, vi);
          sd(*(fi.begin()+i0), *(fi.begin()+i1), xi, ui);
          sd(*(fi.begin()+i3), *(fi.begin()+i2), yi, vr);

          sd(ui, vi, *(fi.begin()+i1), *(fi.begin()+i3));
          sd(xi, yi, *(fi.begin()+i0), *(fi.begin()+i2));
          sd(ur, vr, *(fr.begin()+i1), *(fr.begin()+i3));
          sd(xr, yr, *(fr.begin()+i0), *(fr.begin()+i2));
        }
      }
    }
    ldm += 2*lx;
    for ( ; ldm<=ldn; ldm+=lx)
    {
      i_t m = (1UL<<ldm);
      i_t m4 = (m>>lx);
      const auto ph0 = T(2)/m;
      if(m4 >= eve::expected_cardinal_v<T>)
      {
        auto js = eve::views::iota(T{0}, m4);
        auto phs= eve::views::iota_with_step(T{0}, ph0, m4);
        auto view = eve::views::zip(js, phs);
        auto doit = [n, m, m4, &fr, &fi](auto zz, auto ignore){
          auto [j, ph] = load[ignore](zz);
          auto cs  = exp_ipi(ph);
          using c_t =  decltype(cs);
          auto cs2 = sqr(cs);
          auto cs3 = cs2*cs;
          for (i_t r=0; r<n; r+=m)
          {
            i_t i0 = j.get(0) + r;
            i_t i1 = i0 + m4;
            i_t i2 = i1 + m4;
            i_t i3 = i2 + m4;
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
            auto  [xr, xi] = cs2*c_t(fri1, fii1);

            using wT_t = decltype(xr);
            wT_t ur, ui;
            srd(xr, fri0, ur);
            srd(xi, fii0, ui);
            auto [yr, vr] = cs*c_t(fri2, fii2);
            auto [vi, yi] = cs3*c_t(fri3, fii3);
            sd(yr, vi);
            sd(yi, vr);
            sd(ur, vr, fri1, fri3);
            sd(ui, vi, fii1, fii3);
            sd(xr, yr, fri0, fri2);
            sd(xi, yi, fii0, fii2);
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
        eve::algo::for_each[eve::algo::allow_frequency_scaling](view, doit);
      }
      else
      {
        T ph(0);
        using c_t =  eve::complex<T>;
        for (i_t j=0; j<m4; j++)
        {
          auto cs  = exp_ipi(ph);
          ph += ph0;
          auto cs2 = sqr(cs);
          auto cs3 = cs2*cs;
          for (i_t r=0; r<n; r+=m)
          {
            i_t i0 = j + r;
            i_t i1 = i0 + m4;
            i_t i2 = i1 + m4;
            i_t i3 = i2 + m4;
            auto [xr, xi] = cs2*c_t(*(frbeg+i1), *(fibeg+i1));
            T ur, ui;
            srd(xr, *(frbeg+i0), ur);
            srd(xi, *(fibeg+i0), ui);
            auto [yr, vr] = cs*c_t(*(frbeg+i2), *(fibeg+i2));
            auto [vi, yi] = cs3*c_t(*(frbeg+i3), *(fibeg+i3));
            sd(yr, vi);
            sd(yi, vr);
            sd(ur, vr, *(frbeg+i1), *(frbeg+i3));
            sd(ui, vi, *(fibeg+i1), *(fibeg+i3));
            sd(xr, yr, *(frbeg+i0), *(frbeg+i2));
            sd(xi, yi, *(fibeg+i0), *(fibeg+i2));
          }
        }
      }
    }
    scaleit(fr, fi, fac);
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_dit4_(EVE_SUPPORTS(cpu_), aos_type const &
              , R &f
              , T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto n =  std::size(f);
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
    auto [fr, fi] = soac2ri(f);
    aos(fft_dit4)(fr, fi, fac);
  }

}
