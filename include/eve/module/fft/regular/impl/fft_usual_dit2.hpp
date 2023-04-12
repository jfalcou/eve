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
   if (fac != T(1))
     for(size_t i=0; i < n; ++i) f[i] *= fac;
  }

//   /////////////////////////////////////////////////////////////////////////////////////////
//   template<value T, value T1>
//   constexpr auto fft_dt2_scalar_(EVE_SUPPORTS(cpu_)
//                          , eve::algo::soa_vector<eve::complex<T>> & f
//                          , T1 fac
//                          , T1 s) noexcept
//   {

//       using  c_t = complex<T>;
//     auto n =  f.size();
//     using i_t = decltype(n);
//     EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
//     std::vector<c_t> c(n);
//     auto ldn = eve::countr_zero(n); //eve::log2(n));

//     f = revbin_permute(f);

//     for (i_t ldm=1; ldm<=ldn; ++ldm)
//     {
//       const i_t m = (1UL<<ldm);
//       const i_t mh = (m>>1);
//       const T phi = s/T(mh);
//       for (i_t r=0; r<n; r+=m)
//       {
//         for (i_t j=0; j<mh; ++j)
//         {
//           i_t i0 = r + j;
//           i_t i1 = i0 + mh;

//           auto u = f.get(i0);
//           auto v = f.get(i1)*exp_ipi( phi*j );

//           f[i0] = u + v;
//           f[i1] = u - v;
//         }
//       }
//     }

//     std::cout << "soa vector scalar" << std::endl;
//     for(size_t i=0; i < n; ++i) f[i] *= fac;
//     return f;
//   }


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
      if (cardinal >=  mh)
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
        for (i_t j=0; j<mh; ++j)
        {
          auto w = exp_ipi( phi*j );

          auto doit = [m, &f, w](std::ptrdiff_t j, std::ptrdiff_t mh) {
            EVE_ASSERT(mh > eve::nofs_cardinal_v<T>, "");
            auto s = f.begin() + j;
            auto p = s + mh;

            // maybe uint64_t for doubles
            auto view = eve::views::zip(eve::algo::as_range(s, p), p,
                                        eve::views::iota_with_step(i_t{0}, m));

            // transform does
            eve::algo::for_each[eve::algo::expensive_callable](
              view, [w](auto zz, auto ignore) {
                auto [u_it, v_it, _] = zz;
                auto [u, v, idx] = eve::load[ignore](zz);
                v*=  w;
                eve::store[ignore]((u + v), u_it);
                eve::store[ignore]((u - v), v_it);
              });
          };
          doit(j, mh);
        }
      }
    };
    if (fac != T(1))
      for(size_t i=0; i < n; ++i) f.set(i, f.get(i)*fac);
  }
}
