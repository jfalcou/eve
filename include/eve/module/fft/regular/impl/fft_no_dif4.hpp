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
  // fft depth first decimation in frequency
  template<range R, floating_scalar_value T>
  EVE_FORCEINLINE  void
  fft_no_dif4_(EVE_SUPPORTS(cpu_), aos_type const &, R & f, T fac) noexcept
  requires(eve::is_complex_v<typename R::value_type>)
  {
    auto n =  f.size();
    using i_t = decltype(n);
    i_t lx = 2;
    EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
    auto ldn = eve::countr_zero(n); //eve::log2(n));

    for (i_t ldm=ldn; ldm>=lx; ldm-=lx)
    {
        i_t m = (1UL<<ldm);
        i_t m4 = (m>>lx);
        auto ph0 = rec(T(m));

        for (i_t j=0; j<m4; j++)
        {
            auto phi = j * ph0;
            auto e  = exp_ipi(phi);
            auto e2 = exp_ipi(T(2)*phi);
            auto e3 = exp_ipi(T(3)*phi);

            for (i_t r=0; r<n; r+=m)
            {
                i_t i0 = j + r;
                i_t i1 = i0 + m4;
                i_t i2 = i1 + m4;
                i_t i3 = i2 + m4;

                auto a0 = *(f.data()+i0); //f[i0];
                auto a1 = *(f.data()+i1); //f[i1];
                auto a2 = *(f.data()+i2); //f[i2];
                auto a3 = *(f.data()+i3); //f[i3];

                auto t0 = (a0+a2) + (a1+a3);
                auto t2 = (a0+a2) - (a1+a3);

                auto t1 = (a0-a2) + (a1-a3);
                auto t3 = (a0-a2) - (a1-a3);

                t1 *= e;
                t2 *= e2;
                t3 *= e3;

                *(f.data()+i0)/*f[i0]*/ = t0;
                *(f.data()+i1)/*f[i1]*/ = t2;  // (!)
                *(f.data()+i2)/*f[i2]*/ = t1;  // (!)
                *(f.data()+i3)/*f[i3]*/ = t3;
            }
        }
    }

    if ( (ldn&1)!=0 )  // n is not a power of 4, need a radix-2 step
    {
        for (i_t r=0; r<n; r+=2)
        {
          auto a0 = *(f.data()+r);   //f[r];
          auto a1 = *(f.data()+r+1); //f[r+1];

          *(f.data()+r)   /*f[r]*/   = a0 + a1;
          *(f.data()+r+1) /*f[r+1]*/ = a0 - a1;
        }
    }

    aos(revbin_permute)(f);
    if (fac != T(1))
      for(size_t i=0; i < n; ++i) f[i] *= fac;
  }

//   template<range R, floating_scalar_value T>
//   EVE_FORCEINLINE constexpr void
//   fft_no_df_dif4_(EVE_SUPPORTS(cpu_), soa_type const &, R & f, T fac) noexcept
//   requires(eve::is_complex_v<typename R::value_type>)
//   {
//     constexpr size_t cardinal = eve::nofs_cardinal_v<T>;
//     using  c_t = complex<T>;
//     auto n =  f.size();
//     using i_t = decltype(n);
//     EVE_ASSERT(is_pow2(n),  "data size is not a power of 2");
//     std::vector<c_t> c(n);
//     auto ldn = eve::countr_zero(n);
//     for (i_t ldm=ldn; ldm>=1; --ldm)
//     {
//       const i_t m = (1UL<<ldm);
//       const i_t mh = m >> 1;
//       const T  phi = rec(T(mh));
//       if (cardinal >=  mh)
//       {
//         for (i_t r=0; r<n; r+=m)
//         {
//          for (i_t j=0; j<mh; ++j)
//           {
//             i_t i0 = r + j;
//             i_t i1 = i0 + mh;
//             auto u = f.get(i0);
//             auto v = f.get(i1);
//             f.set(i0, (u + v));
//             f.set(i1, (u - v)*exp_ipi( phi*j));
//           }
//         }
//       }
//       else
//       {
//         for (i_t r=0; r<n; r+=m)
//         {
//           auto doit = [phi](
//             eve::algo::soa_vector<eve::complex<T>>& f,
//             std::ptrdiff_t r,
//             std::ptrdiff_t mh) {
//             EVE_ASSERT(mh > eve::nofs_cardinal_v<T>, "");
//             auto s = f.begin() + r;
//             auto m = s + mh;

//             // maybe uint64_t for doubles
//             auto view = eve::views::zip(eve::algo::as_range(s, m), m,
//                                         eve::views::iota(std::uint32_t{0}));

//             // transform does
//             eve::algo::for_each[eve::algo::expensive_callable](
//               view, [phi](auto zz, auto ignore) {
//                 auto [u_it, v_it, _] = zz;
//                 auto [u, v, idx] = eve::load[ignore](zz, eve::fixed<cardinal>{});

//                 eve::store[ignore]((u + v), u_it);
//                 eve::store[ignore](
//                   (u - v) * eve::exp_ipi(phi*eve::convert(idx, eve::as<T>{})),
//                   v_it);
//               });
//           };
//           doit(f, r, mh);
//         }
//       }
//     }
//     soa(revbin_permute)(f);
//     if(fac != T(1))
//       for(size_t i=0; i < n; ++i) f.set(i, f.get(i)*fac);
//   }
}
