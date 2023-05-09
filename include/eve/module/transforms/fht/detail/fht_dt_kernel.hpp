//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/complex.hpp>
#include <eve/concept/range.hpp>
#include <eve/module/transforms/utils.hpp>
#include <type_traits>

namespace eve::detail
{
  template < bool initial_radix_16 = true >
  EVE_FORCEINLINE constexpr void
  fht_dt_kernel(auto f, auto log2_n, const bool simd = true) noexcept
  //  requires(std::is_floating_point_v<typename R::value_type>)
  {
    std::cout << "simd " << simd << std::endl;
    auto n = 1UL << log2_n;
    using i_t = decltype(n);
    using e_t = eve::underlying_type_t<std::remove_reference_t<decltype(f[0])>>;
    using c_t =  complex<e_t>;
    [[maybe_unused]] const auto  invsqrt2 = invsqrt_2(as<e_t>());
    [[maybe_unused]] const auto  sqrt2    = sqrt_2(as<e_t>());
    if ( log2_n<=2 )
    {
        if ( log2_n==1 )  // two point fht
        {
            sd(f[0], f[1]);
        }
        else if ( log2_n==2 )  // four point fht
        {
            e_t f0, f1, f2, f3;
            sd(f[0], f[1], f0, f1);
            sd(f[2], f[3], f2, f3);
            sd(f0, f2, f[0], f[2]);
            sd(f1, f3, f[1], f[3]);
        }
        return;
    }

    auto fn = f + n;
    i_t ldk = log2_n & 1;

    if ( ldk==0 )    // log2_n is multiple of 2  => n is a power of 4
    {
      if constexpr(initial_radix_16)
      {
        for (e_t *fi=f; fi<fn; fi+=16)  // radix-16 step
        {
            e_t f0, f1, f2, f3;
            sd(fi[0], fi[1], f0, f1);
            sd(fi[2], fi[3], f2, f3);
            sd(f0, f2, fi[0], fi[2]);
            sd(f1, f3, fi[1], fi[3]);

            sd(fi[4], fi[5], f0, f1);
            sd(fi[6], fi[7], f2, f3);
            sd(f0, f2, fi[4], fi[6]);
            sd(f1, f3, fi[5], fi[7]);

            sd(fi[8], fi[9], f0, f1);
            sd(fi[10], fi[11], f2, f3);
            sd(f0, f2, fi[8], fi[10]);
            sd(f1, f3, fi[9], fi[11]);

            sd(fi[12], fi[13], f0, f1);
            sd(fi[14], fi[15], f2, f3);
            sd(f0, f2, fi[12], fi[14]);
            sd(f1, f3, fi[13], fi[15]);

            sd(fi[0], fi[4], f0, f1);
            sd(fi[8], fi[12], f2, f3);
            sd(f0, f2, fi[0], fi[8]);
            sd(f1, f3, fi[4], fi[12]);

            sd(fi[2], fi[6], f0, f1);
            f3 = sqrt2 * fi[14];
            f2 = sqrt2 * fi[10];
            sd(f0, f2, fi[2], fi[10]);
            sd(f1, f3, fi[6], fi[14]);

            e_t a, b, g0, g1, g2, g3;
            sd(fi[5], fi[7], a, b);
            a *= invsqrt2;
            b *= invsqrt2;
            sd(fi[1], a, f0, f1);
            sd(fi[3], b, g0, g1);
            sd(fi[13], fi[15], a, b);
            a *= invsqrt2;
            b *= invsqrt2;
            sd(fi[9], a, f2, f3);
            sd(fi[11], b, g2, g3);
            e_t c1 = e_t( 0.923879532511286756128183189397); //COS_1_PI_8;  // jjkeep
            e_t s1 =  e_t( 0.382683432365089771728459984029); //SIN_1_PI_8;  // jjkeep
            kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
             //  cmult(s1, c1, f2, g3, b, a);
            sd(f0, a, fi[1], fi[9]);
            sd(g1, b, fi[7], fi[15]);
            kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
//            cmult(c1, s1, g2, f3, b, a);
            sd(g0, a, fi[3], fi[11]);
            sd(f1, b, fi[5], fi[13]);
        }
        ldk = 4;
      }
      else
      {
        for (e_t *fi=f; fi<fn; fi+=4)  // radix-4 step
        {
          e_t f0, f1, f2, f3;
          sd(fi[0], fi[1], f0, f1);
          sd(fi[2], fi[3], f2, f3);
          sd(f0, f2, fi[0], fi[2]);
          sd(f1, f3, fi[1], fi[3]);
        }
        ldk = 2;
      }  // INITIAL_RADIX_16
    }
    else          // ldk==1,  n is no power of 4
    {
      for (double *fi=f; fi<fn; fi+=8)  // radix-8 step
      {
        e_t g0, f0, f1, g1;
        sd(fi[0], fi[1], f0, g0);
        sd(fi[2], fi[3], f1, g1);

        sd(f0, f1);
        sd(g0, g1);

        e_t s1, c1, s2, c2;
        sd(fi[4], fi[5], s1, c1);
        sd(fi[6], fi[7], s2, c2);

        sd(s1, s2);

        sd(f0, s1, fi[0], fi[4]);
        sd(f1, s2, fi[2], fi[6]);

        c1 *= sqrt2;
        c2 *= sqrt2;

        sd(g0, c1, fi[1], fi[5]);
        sd(g1, c2, fi[3], fi[7]);
      }
      ldk = 3;
    }
    for (  ; ldk<log2_n;  ldk+=2)
    {
        i_t k   = 1UL<<ldk;
        i_t kh  = k >> 1;
        i_t k2  = k << 1;
        i_t k3  = k2 + k;
        i_t k4  = k2 << 1;

        for (e_t *fi=f, *gi=f+kh;  fi<fn;  fi+=k4, gi+=k4)
        {
            e_t f0, f1, f2, f3;
            sd(fi[0], fi[k], f0, f1);
            sd(fi[k2], fi[k3], f2, f3);
            sd(f0, f2, fi[0], fi[k2]);
            sd(f1, f3, fi[k], fi[k3]);

            sd(gi[0], gi[k], f0, f1);
            f3 = sqrt2 * gi[k3];
            f2 = sqrt2 * gi[k2];
            sd(f0, f2, gi[0], gi[k2]);
            sd(f1, f3, gi[k], gi[k3]);
        }

        e_t tt = rec(e_t(kh*4));
#if defined USE_TRIG_REC
        e_t s1 = 0.0,  c1 = 1.0;  // jjkeep
        e_t al = sinpi(0.5*tt);  // jjkeep
        al *= (2.0*al);
        e_t be = sinpi(tt);  // jjkeep
#endif  // USE_TRIG_REC

        for (i_t i=1; i<kh; i++)
        {
#if defined USE_TRIG_REC
            {
                e_t t1 = c1;  // jjkeep
                c1 -= (al*t1+be*s1);
                s1 -= (al*s1-be*t1);
            }
#else
            // e_t s1, c1;  // jjkeep
            //SinCos(tt*(double)i, &s1, &c1);  // jjkeep
            auto [s1, c1] = exp_ipi(tt*i);
#endif  // USE_TRIG_REC

            //e_t c2, s2;  // jjkeep
            auto [c2, s2] = sqr(c_t(c1, s1));
            for (e_t *fi=f+i, *gi=f+k-i;  fi<fn;  fi+=k4, gi+=k4)
            {
                e_t a, b, g0, f0, f1, g1, f2, g2, f3, g3;
                //               cmult(s2, c2, fi[k], gi[k], b, a);
                kumi::tie(b, a) = c_t(s2, c2)*c_t(fi[k], gi[k]);
                sd(fi[0], a, f0, f1);
                sd(gi[0], b, g0, g1);

                kumi::tie(b, a) = c_t(s2, c2)*c_t(fi[k3], gi[k3]);
//                cmult(s2, c2, fi[k3], gi[k3], b, a);
                sd(fi[k2], a, f2, f3);
                sd(gi[k2], b, g2, g3);

                kumi::tie(b, a) = c_t(s1, c1)*c_t(f2, g3);
//                cmult(s1, c1, f2, g3, b, a);
                sd(f0, a, fi[0], fi[k2]);
                sd(g1, b, gi[k], gi[k3]);

//                cmult(c1, s1, g2, f3, b, a);
                kumi::tie(b, a) = c_t(c1, s1)*c_t(g2, f3);
                sd(g0, a, gi[0], gi[k2]);
                sd(f1, b, fi[k], fi[k3]);
            }
        }
    }
  }
}
