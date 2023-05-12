//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

#include "test.hpp"
#include "../measures.hpp"
#include <eve/module/transforms/detail/pr.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/transforms.hpp>
#include <vector>


#include <cmath>  // M_PI, M_SQRT1_2
#define COS_1_PI_8  0.923879532511286756128183189397
#define SIN_1_PI_8  0.382683432365089771728459984029

// tuning parameter:
// define to use trig recurrence:
// (and possibly lose some precision, see below)
//#define USE_TRIG_REC
// with type 'long double' slight speed loss on my machine,
// with type 'double' little speed gain.

#if defined USE_TRIG_REC
//#warning 'FYI: fht(double *, ulong) uses trig recursion'
#endif

// // tuning parameter:
// #define  INITIAL_RADIX_16  1  // 0 or 1 (default)
// //
// #if  ( INITIAL_RADIX_16==1 )
// //#warning 'FYI: INITIAL_RADIX_16 set in fht_dit(double *, ulong)'
// #else
// #warning 'INITIAL_RADIX_16 is NOT SET in fht_dit(double *, ulong)'
// #endif

// namespace pipo
// {
//   template <typename Type>
//   static inline void sumdiff(Type a, Type b, Type &s, Type &d)
//   // {s, d}  <--| {a+b, a-b}
//   { s=a+b; d=a-b; }

//   static inline void csqr(double a, double b,
//                           double &u, double &v)
//   // {u,v} <--| {a*a-b*b, 2*a*b}
//   {
//     u = a * a - b * b;
//     v = a * b;
//     v += v;
//   }

//   static inline void cmult(double c, double s,
//                            double &u, double &v)
//   // {u,v} <--| u = u*c-v*s;  v = u*s+v*c
//   {
//     double t = u * s + v * c;
//     u *= c;
//     u -= v * s;
//     v = t;
//   }

//   void
//   fht_dit_core(double *f, ulong ldn)
//   // Decimation in time (DIT) FHT.
//   // Input data must be in revbin_permuted order.
//   // ldn := base-2 logarithm of the array length.
//   {
//     if ( ldn<=2 )
//     {
//       if ( ldn==1 )  // two point fht
//       {
//         sd(f[0], f[1]);
//       }
//       else if ( ldn==2 )  // four point fht
//       {
//         double f0, f1, f2, f3;
//         sumdiff(f[0], f[1], f0, f1);
//         sumdiff(f[2], f[3], f2, f3);
//         sumdiff(f0, f2, f[0], f[2]);
//         sumdiff(f1, f3, f[1], f[3]);
//       }
//       return;
//     }

//     const ulong n = (1UL<<ldn);
//     const double *fn = f + n;
//     ulong ldk = ldn & 1;

//     if ( ldk==0 )    // ldn is multiple of 2  => n is a power of 4
//     {
// #if  ( INITIAL_RADIX_16==1 )
//       for (double *fi=f; fi<fn; fi+=16)  // radix-16 step
//       {
//         double f0, f1, f2, f3;
//         sumdiff(fi[0], fi[1], f0, f1);
//         sumdiff(fi[2], fi[3], f2, f3);
//         sumdiff(f0, f2, fi[0], fi[2]);
//         sumdiff(f1, f3, fi[1], fi[3]);

//         sumdiff(fi[4], fi[5], f0, f1);
//         sumdiff(fi[6], fi[7], f2, f3);
//         sumdiff(f0, f2, fi[4], fi[6]);
//         sumdiff(f1, f3, fi[5], fi[7]);

//         sumdiff(fi[8], fi[9], f0, f1);
//         sumdiff(fi[10], fi[11], f2, f3);
//         sumdiff(f0, f2, fi[8], fi[10]);
//         sumdiff(f1, f3, fi[9], fi[11]);

//         sumdiff(fi[12], fi[13], f0, f1);
//         sumdiff(fi[14], fi[15], f2, f3);
//         sumdiff(f0, f2, fi[12], fi[14]);
//         sumdiff(f1, f3, fi[13], fi[15]);

//         sumdiff(fi[0], fi[4], f0, f1);
//         sumdiff(fi[8], fi[12], f2, f3);
//         sumdiff(f0, f2, fi[0], fi[8]);
//         sumdiff(f1, f3, fi[4], fi[12]);

//         sumdiff(fi[2], fi[6], f0, f1);
//         f3 = M_SQRT2 * fi[14];
//         f2 = M_SQRT2 * fi[10];
//         sumdiff(f0, f2, fi[2], fi[10]);
//         sumdiff(f1, f3, fi[6], fi[14]);

//         double a, b, g0, g1, g2, g3;
//         sumdiff(fi[5], fi[7], a, b);
//         a *= M_SQRT1_2;
//         b *= M_SQRT1_2;
//         sumdiff(fi[1], a, f0, f1);
//         sumdiff(fi[3], b, g0, g1);
//         sumdiff(fi[13], fi[15], a, b);
//         a *= M_SQRT1_2;
//         b *= M_SQRT1_2;
//         sumdiff(fi[9], a, f2, f3);
//         sumdiff(fi[11], b, g2, g3);
//         double c1 = COS_1_PI_8;  // jjkeep
//         double s1 = SIN_1_PI_8;  // jjkeep
//         cmult(s1, c1, f2, g3, b, a);
//         sumdiff(f0, a, fi[1], fi[9]);
//         sumdiff(g1, b, fi[7], fi[15]);
//         cmult(c1, s1, g2, f3, b, a);
//         sumdiff(g0, a, fi[3], fi[11]);
//         sumdiff(f1, b, fi[5], fi[13]);
//       }
//       ldk = 4;
// #else  // INITIAL_RADIX_16
//       for (double *fi=f; fi<fn; fi+=4)  // radix-4 step
//       {
//         double f0, f1, f2, f3;
//         sumdiff(fi[0], fi[1], f0, f1);
//         sumdiff(fi[2], fi[3], f2, f3);
//         sumdiff(f0, f2, fi[0], fi[2]);
//         sumdiff(f1, f3, fi[1], fi[3]);
//       }
//       ldk = 2;
// #endif  // INITIAL_RADIX_16
//     }
//     else          // ldk==1,  n is no power of 4
//     {
//       for (double *fi=f; fi<fn; fi+=8)  // radix-8 step
//       {
//         double g0, f0, f1, g1;
//         sumdiff(fi[0], fi[1], f0, g0);
//         sumdiff(fi[2], fi[3], f1, g1);

//         sumdiff(f0, f1);
//         sumdiff(g0, g1);

//         double s1, c1, s2, c2;
//         sumdiff(fi[4], fi[5], s1, c1);
//         sumdiff(fi[6], fi[7], s2, c2);

//         sumdiff(s1, s2);

//         sumdiff(f0, s1, fi[0], fi[4]);
//         sumdiff(f1, s2, fi[2], fi[6]);

//         c1 *= M_SQRT2;
//         c2 *= M_SQRT2;

//         sumdiff(g0, c1, fi[1], fi[5]);
//         sumdiff(g1, c2, fi[3], fi[7]);
//       }
//       ldk = 3;
//     }


//     for (  ; ldk<ldn;  ldk+=2)
//     {
//       ulong k   = 1UL<<ldk;
//       ulong kh  = k >> 1;
//       ulong k2  = k << 1;
//       ulong k3  = k2 + k;
//       ulong k4  = k2 << 1;

//       for (double *fi=f, *gi=f+kh;  fi<fn;  fi+=k4, gi+=k4)
//       {
//         double f0, f1, f2, f3;
//         sumdiff(fi[0], fi[k], f0, f1);
//         sumdiff(fi[k2], fi[k3], f2, f3);
//         sumdiff(f0, f2, fi[0], fi[k2]);
//         sumdiff(f1, f3, fi[k], fi[k3]);

//         sumdiff(gi[0], gi[k], f0, f1);
//         f3 = M_SQRT2 * gi[k3];
//         f2 = M_SQRT2 * gi[k2];
//         sumdiff(f0, f2, gi[0], gi[k2]);
//         sumdiff(f1, f3, gi[k], gi[k3]);
//       }

//       double tt = M_PI_4/(double)kh;  // jjkeep
// #if defined USE_TRIG_REC
//       double s1 = 0.0,  c1 = 1.0;  // jjkeep
//       double al = sin(0.5*tt);  // jjkeep
//       al *= (2.0*al);
//       double be = sin(tt);  // jjkeep
// #endif  // USE_TRIG_REC

//       for (ulong i=1; i<kh; i++)
//       {
// #if defined USE_TRIG_REC
//         {
//           double t1 = c1;  // jjkeep
//           c1 -= (al*t1+be*s1);
//           s1 -= (al*s1-be*t1);
//         }
// #else
//         double s1, c1;  // jjkeep
//         eve::sincos(tt*(double)i, &s1, &c1);  // jjkeep
// #endif  // USE_TRIG_REC

//         double c2, s2;  // jjkeep
//         csqr(c1, s1, c2, s2);

//         for (double *fi=f+i, *gi=f+k-i;  fi<fn;  fi+=k4, gi+=k4)
//         {
//           double a, b, g0, f0, f1, g1, f2, g2, f3, g3;
//           cmult(s2, c2, fi[k], gi[k], b, a);
//           sumdiff(fi[0], a, f0, f1);
//           sumdiff(gi[0], b, g0, g1);

//           cmult(s2, c2, fi[k3], gi[k3], b, a);
//           sumdiff(fi[k2], a, f2, f3);
//           sumdiff(gi[k2], b, g2, g3);

//           cmult(s1, c1, f2, g3, b, a);
//           sumdiff(f0, a, fi[0], fi[k2]);
//           sumdiff(g1, b, gi[k], gi[k3]);

//           cmult(c1, s1, g2, f3, b, a);
//           sumdiff(g0, a, gi[0], gi[k2]);
//           sumdiff(f1, b, fi[k], fi[k3]);
//         }
//       }
//     }
//   }
//   // -------------------------

//   void
//   fht_dit(double *f, ulong ldn)
//   // Fast Hartley Transform.
//   // Split-radix decimation in time (DIT) algorithm.
//   // ldn := base-2 logarithm of the array length.
//   {
//     if ( ldn<=2 )
//     {
//       if ( ldn==1 )  // two point fht
//       {
//         sumdiff(f[0], f[1]);
//       }
//       else if ( ldn==2 )  // four point fht
//       {
//         double f0, f1, f2, f3;
//         sumdiff(f[0], f[2], f0, f1);
//         sumdiff(f[1], f[3], f2, f3);
//         sumdiff(f0, f2, f[0], f[2]);
//         sumdiff(f1, f3, f[1], f[3]);
//       }

//       return;
//     }

//     revbin_permute(f, 1UL<<ldn);
//     fht_dit_core(f, ldn);
//   }
//   // -------------------------
// }


TTS_CASE_TPL("Check naive_ht", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr(std::same_as<eve::element_type_t<T>, double> && eve::cardinal_v<T> == 1)
  {
    size_t N = 1 << 15;
    std::cout << tts::typename_<T> << std::endl; ;
    using e_t = typename T::value_type;
    std::vector<e_t> a(N), b(N), orig(N), naiv(N);
    for(size_t i=0; i < N ; ++i) naiv[i] = orig[i] = a[i] = b[i] = i+1;
    eve::large_df_fht(a, e_t(1.0), true);
    eve::large_dt_fht(b, e_t(1.0), true);
    for(size_t i=0; i <N ; ++i){
      TTS_ABSOLUTE_EQUAL(a[i],b[i], 0.001);
    }
//     eve::naive_ht(a, e_t(2)/(N)); //inverse ht
//     for(size_t i=0; i <N ; ++i){
//       TTS_ABSOLUTE_EQUAL(a[i],orig[i], 100*eve::eps(eve::as<e_t>()));
//     }
  }
};
