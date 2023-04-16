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
  // Decimation in time (DIT) radix-2 FFT.
  // Compared to depth-first FFT this one
  // - does less trig computations
  // - is (far) worse memory local

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  fft_usual_dit2_(EVE_SUPPORTS(cpu_), aos_type const &, R & f, T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto n =  f.size();
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "fft_df_dit2: data size is not a power of 2");
    auto ldn = eve::countr_zero(n); //eve::log2(n));
    aos(revbin_permute)(f);

   for (i_t ldm=1; ldm<=ldn; ++ldm)
   {
     const i_t m = (1UL<<ldm);
     const i_t mh = (m>>1);
     const T phi = rec(T(mh));
     for (i_t j=0; j<mh; ++j)
     {
       auto w = exp_ipi( phi*j );
       for (i_t r=0; r<n; r+=m)
       {
         i_t i0 = r + j;
         i_t i1 = i0 + mh;
          auto pi0 = f.data()+i0;
          auto pi1 = f.data()+i1;
          auto u =  *pi0 ;
          auto v =  *pi1*w;
          *pi0 = u + v;
          *pi1 = u - v;
       }
     }
   }
   aos(scaleit)(f, fac);
//    if (fac != T(1))
//      for(size_t i=0; i < n; ++i) f[i] *= fac;
  }

  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE constexpr void
  fft_usual_dit2_(EVE_SUPPORTS(cpu_), soa_type const &, R & f, T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    size_t cardinal = eve::nofs_cardinal_v<T>;
    auto n =  f.size();
    using i_t = decltype(n);
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    auto ldn = eve::countr_zero(n);
    soa(revbin_permute)(f);

    for (i_t ldm=1; ldm<=ldn; ++ldm)
    {
      const i_t m = (1UL<<ldm);
      const i_t mh = (m>>1);
      const T phi = rec(T(mh));
      if (cardinal >=  m)
      {
        for (i_t j=0; j<mh; ++j)
        {
          auto w = exp_ipi( phi*j );
          for (i_t r=0; r<n; r+=m)
          {
            i_t i0 = r + j;
            i_t i1 = i0 + mh;
            auto u = f.get(i0);
            auto v = f.get(i1)*w;
            f.set(i0, u + v);
            f.set(i1, u - v);
          }
        }
      }
      else
      {
        auto js = eve::views::iota(T{0}, mh);
        auto doit = [phi, n, m, mh, &f](auto zz, auto ignore){
          auto jj = load[ignore](zz);
          auto w = exp_ipi( phi*jj); //eve::convert(j, eve::as<T>{}));
          for (i_t r=0; r<n; r+=m)
          {
            auto i0 = jj.get(0)+r; ;
            auto i1 = i0 + mh;
            using cw_t = wide<eve::complex<T>>;
            auto init0 =  [i0, &f](auto i, auto){return f.get(i+i0);};
            auto init1 =  [i1, &f](auto i, auto){return f.get(i+i1);};
            cw_t u(init0);
            cw_t v(init1);
            v*= w;
            store[ignore](u + v, f.data()+i0);
            store[ignore](u - v, f.data()+i1);
          }
        };
        eve::algo::for_each[eve::algo::expensive_callable](js, doit);
      }
    }
    soa(scaleit)(f, fac);
//     if (fac != T(1))
//       for(size_t i=0; i < n; ++i) f.set(i, f.get(i)*fac);
  }
}
