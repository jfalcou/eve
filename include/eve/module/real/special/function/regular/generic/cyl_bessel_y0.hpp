//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/cyl_bessel_j0.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/log.hpp>
#include <eve/function/none.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <eve/module/real/special/detail/evaluate_rational.hpp>
#include <array>

namespace eve::detail
//still to be done
{

 //  template<floating_real_value T>
//   EVE_FORCEINLINE T cyl_bessel_y0_(EVE_SUPPORTS(cpu_), T x) noexcept
//   {
//     // ensure x > 0 y0 is an even function
//     using elt_t =  element_type_t<T>;
//     x = eve::abs(x);
//     auto Pi = eve::pi(as(x));

//     auto evaluate = [Pi](auto x, auto x1, auto x11, auto x12, auto P, auto Q)
//       {
//         T y = sqr(x);
//         T z = 2 * log(x/x1) * cyl_bessel_j0(x) / Pi;
//         T r = evaluate_rational(P, Q, y);
//         T factor = (x + x1) * ((x - x11/256) - x12);
//         return fma(factor, r, z); //z + factor * r;
//       };

//     using elt_t =  element_type_t<T>;
//     if constexpr(scalar_value<T>)
//     {
//       if (x == 0)          return minf(as(x)); // x is 0
//       if (x == inf(as(x))) return zero(as(x)); // x is infinite
//       if (is_nan(x))       return x;           // x is nan
//       if (x <= 3)          return br_3(x);     // x in (0, 5.5]
//       if (x <= 5.5)        return br_5_5(x);   // x in (5.5, 8]
//       return br_large(x);                      // x in (8, \infty)
//     }
//     else //simd
//     {
// //       if constexpr(has_native_abi_v<T>)
// //       {
// //         auto r = nan(as(x));
// //         auto notdone = is_gez(x);
// //         if( eve::any(notdone) )
// //         {
// //           notdone = next_interval(br_4,  notdone, x <= T(4), r, x);
// //           if( eve::any(notdone) )
// //           {
// //             notdone = next_interval(br_8,  notdone, x <= T(8), r, x);
// //             if( eve::any(notdone) )
// //             {
// //               notdone = last_interval(br_large,  notdone, r, x);
// //             }
// //           }
// //         }
// //         r = if_else (is_eqz(x), one(as(x)), r);
// //         r = if_else (x == inf(as(x)), zero, r);
// //         return r;
// //       }
// //       else return apply_over(cyl_bessel_j0, x);
//     }
//   }


//   template<floating_real_scalar_value T>
//   EVE_FORCEINLINE T cyl_bessel_y0_(EVE_SUPPORTS(cpu_), T x) noexcept
//   {
//     auto Pi = eve::pi(as(x));
//     if (x < 0) x = -x;
//     if (x == 0) return minf(as(x));
//     if (x == inf(as(x))) return zero(as(x));
//     auto evaluate = [Pi](auto x, auto x1, auto x11, auto x12, auto P, auto Q)
//       {
//         T y = sqr(x);
//         T z = 2 * log(x/x1) * cyl_bessel_j0(x) / Pi;

// //        T r = horner( y, P)/ horner( y, Q);
//         T r = evaluate_rational(P, Q, y);
//         T factor = (x + x1) * ((x - x11/256) - x12);
//         return fma(factor, r, z); //z + factor * r;
//       };

//     if (x <= T(3))                       // x in (0, 3]
//     {
//       constexpr std::array<T, 6> P1 = {
//         1.0723538782003176831e+11
//         , -8.3716255451260504098e+09
//         ,  2.0422274357376619816e+08
//         , -2.1287548474401797963e+06
//         ,  1.0102532948020907590e+04
//         , -1.8402381979244993524e+01
//       };
//       constexpr std::array<T, 6> Q1 = {
//         5.8873865738997033405e+11
//         , 8.1617187777290363573e+09
//         , 5.5662956624278251596e+07
//         , 2.3889393209447253406e+05
//         , 6.6475986689240190091e+02
//         , 1.0
//       };
//       constexpr T
//         x1  =   8.9357696627916752158e-01,
//         x11 =   2.280e+02,
//         x12 =   2.9519662791675215849e-03;
//       return evaluate(x, x1, x11, x12, P1, Q1);
//     }
//     else if (x <= T(5.5))                  // x in (3, 5.5]
//     {
//       constexpr T
//         x2  =   3.9576784193148578684e+00,
//         x21 =   1.0130e+03,
//         x22 =   6.4716931485786837568e-04;
//       constexpr std::array<T, 7>  P2 = {
//         -2.2213976967566192242e+13
//         , -5.5107435206722644429e+11
//         ,  4.3600098638603061642e+10
//         , -6.9590439394619619534e+08
//         ,  4.6905288611678631510e+06
//         , -1.4566865832663635920e+04
//         ,  1.7427031242901594547e+01
//       };
//       constexpr std::array<T, 7> Q2 = {
//         4.3386146580707264428e+14
//         , 5.4266824419412347550e+12
//         , 3.4015103849971240096e+10
//         , 1.3960202770986831075e+08
//         , 4.0669982352539552018e+05
//         , 8.3030857612070288823e+02
//         , 1.0
//       };
//       return evaluate(x, x2, x21, x22, P2, Q2);
//     }
//     else if (x <= T(8))                  // x in (5.5, 8]
//     {
//       constexpr T
//         x3  =   7.0860510603017726976e+00,
//         x31 =   1.8140e+03,
//         x32 =   1.1356030177269762362e-04;
//       constexpr std::array<T, 8> P3 = {
//         -8.0728726905150210443e+15
//         ,  6.7016641869173237784e+14
//         , -1.2829912364088687306e+11
//         , -1.9363051266772083678e+11
//         ,  2.1958827170518100757e+09
//         , -1.0085539923498211426e+07
//         ,  2.1363534169313901632e+04
//         , -1.7439661319197499338e+01
//       };
//       constexpr std::array<T, 8> Q3 = {
//         3.4563724628846457519e+17
//         , 3.9272425569640309819e+15
//         , 2.2598377924042897629e+13
//         , 8.6926121104209825246e+10
//         , 2.4727219475672302327e+08
//         , 5.3924739209768057030e+05
//         , 8.7903362168128450017e+02
//         , 1.0
//       };
//       return evaluate(x, x3, x31, x32, P3, Q3);
//     }
//     else                                // x in (8, \infty)
//     {
//       constexpr std::array<T, 6> PC = {
//         2.2779090197304684302e+04
//         , 4.1345386639580765797e+04
//         , 2.1170523380864944322e+04
//         , 3.4806486443249270347e+03
//         , 1.5376201909008354296e+02
//         , 8.8961548424210455236e-01
//       };
//       constexpr std::array<T, 6> QC = {
//         2.2779090197304684318e+04
//         , 4.1370412495510416640e+04
//         , 2.1215350561880115730e+04
//         , 3.5028735138235608207e+03
//         , 1.5711159858080893649e+02
//         , 1.0
//       };
//       constexpr std::array<T, 6> PS = {
//         -8.9226600200800094098e+01
//         , -1.8591953644342993800e+02
//         , -1.1183429920482737611e+02
//         , -2.2300261666214198472e+01
//         , -1.2441026745835638459e+00
//         , -8.8033303048680751817e-03
//       };
//       constexpr std::array<T, 6> QS = {
//         5.7105024128512061905e+03
//         , 1.1951131543434613647e+04
//         , 7.2642780169211018836e+03
//         , 1.4887231232283756582e+03
//         , 9.0593769594993125859e+01
//         , 1.0
//       };
//       T y = T(8)/x;
//       T y2 = sqr(y);
//       T rc = evaluate_rational(PC, QC, y2);//horner( y2, PC)/ horner( y2, QC);
//       T rs = evaluate_rational(PS, QS, y2);//horner( y2, PS)/ horner( y2, QS);
//       T factor = rsqrt(Pi*x);
//       //
//       // The following code is really just:
//       //
//       // T z = x - 0.25f * Pi
//       // value = factor * (rc * sin(z) + y * rs * cos(z));
//       //
//       // But using the sin/cos addition formulae and constant values for
//       // sin/cos of PI/4 which then cancel part of the "factor" term as they're all
//       // 1 / sqrt(2):
//       //
//      auto [sx, cx] = sincos(x);
//      return factor*fma(y, rs * (cx + sx), rc * (sx - cx));
//     }
//   }


//   template<floating_real_simd_value T>
//   EVE_FORCEINLINE T cyl_bessel_y0_(EVE_SUPPORTS(cpu_), T x) noexcept
//   {
//     if constexpr(has_native_abi_v<T>)
//     {
//       using v_t =  element_type_t<T>;
//       auto Pi = eve::pi(as(x));
//       T j0opi =  cyl_bessel_j0(x) / Pi;
//       x =  eve::abs(x);
//       auto evaluate = [j0opi](auto x, auto x1, auto x11, auto x12, auto P, auto Q)
//         {
//           T y = sqr(x);
//           T z = 2 * log(x/x1) * j0opi;
// //        T r = horner( y, P)/ horner( y, Q);
//           T r = evaluate_rational(P, Q, y);
//           T factor = (x + x1) * ((x - x11/256) - x12);
//           return fma(factor, r, z);
//         };

//       auto br_3 = [evaluate](auto x){
//         x =  if_else(x <= T(3), x, zero);
//         constexpr std::array<v_t, 6> P1 = {
//           1.0723538782003176831e+11
//           , -8.3716255451260504098e+09
//           ,  2.0422274357376619816e+08
//           , -2.1287548474401797963e+06
//           ,  1.0102532948020907590e+04
//           , -1.8402381979244993524e+01
//         };
//         constexpr std::array<v_t, 6> Q1 = {
//           5.8873865738997033405e+11
//           , 8.1617187777290363573e+09
//           , 5.5662956624278251596e+07
//           , 2.3889393209447253406e+05
//           , 6.6475986689240190091e+02
//           , 1.0
//         };
//         constexpr v_t
//         x1  =   8.9357696627916752158e-01,
//         x11 =   2.280e+02,
//         x12 =   2.9519662791675215849e-03;
//         return evaluate(x, x1, x11, x12, P1, Q1);
//       };

//       auto br_5 = [evaluate](auto x){
//         constexpr v_t
//         x2  =   3.9576784193148578684e+00,
//         x21 =   1.0130e+03,
//         x22 =   6.4716931485786837568e-04;
//         constexpr std::array<v_t, 7>  P2 = {
//           -2.2213976967566192242e+13
//           , -5.5107435206722644429e+11
//           ,  4.3600098638603061642e+10
//           , -6.9590439394619619534e+08
//           ,  4.6905288611678631510e+06
//           , -1.4566865832663635920e+04
//           ,  1.7427031242901594547e+01
//         };
//         constexpr std::array<v_t, 7> Q2 = {
//           4.3386146580707264428e+14
//           , 5.4266824419412347550e+12
//           , 3.4015103849971240096e+10
//           , 1.3960202770986831075e+08
//           , 4.0669982352539552018e+05
//           , 8.3030857612070288823e+02
//           , 1.0
//         };
//         return evaluate(x, x2, x21, x22, P2, Q2);
//       };

//       auto br_8 = [evaluate](auto x){
//         constexpr v_t
//         x3  =   7.0860510603017726976e+00,
//         x31 =   1.8140e+03,
//         x32 =   1.1356030177269762362e-04;
//         constexpr std::array<v_t, 8> P3 = {
//           -8.0728726905150210443e+15
//           ,  6.7016641869173237784e+14
//           , -1.2829912364088687306e+11
//           , -1.9363051266772083678e+11
//           ,  2.1958827170518100757e+09
//           , -1.0085539923498211426e+07
//           ,  2.1363534169313901632e+04
//           , -1.7439661319197499338e+01
//         };
//         constexpr std::array<v_t, 8> Q3 = {
//           3.4563724628846457519e+17
//           , 3.9272425569640309819e+15
//           , 2.2598377924042897629e+13
//           , 8.6926121104209825246e+10
//           , 2.4727219475672302327e+08
//           , 5.3924739209768057030e+05
//           , 8.7903362168128450017e+02
//           , 1.0
//         };
//         return evaluate(x, x3, x31, x32, P3, Q3);
//       };

//       auto br_large = [Pi](auto x){
//         constexpr std::array<v_t, 6> PC = {
//           2.2779090197304684302e+04
//           , 4.1345386639580765797e+04
//           , 2.1170523380864944322e+04
//           , 3.4806486443249270347e+03
//           , 1.5376201909008354296e+02
//           , 8.8961548424210455236e-01
//         };
//         constexpr std::array<v_t, 6> QC = {
//           2.2779090197304684318e+04
//           , 4.1370412495510416640e+04
//           , 2.1215350561880115730e+04
//           , 3.5028735138235608207e+03
//           , 1.5711159858080893649e+02
//           , 1.0
//         };
//         constexpr std::array<v_t, 6> PS = {
//           -8.9226600200800094098e+01
//           , -1.8591953644342993800e+02
//           , -1.1183429920482737611e+02
//           , -2.2300261666214198472e+01
//           , -1.2441026745835638459e+00
//           , -8.8033303048680751817e-03
//         };
//         constexpr std::array<v_t, 6> QS = {
//           5.7105024128512061905e+03
//           , 1.1951131543434613647e+04
//           , 7.2642780169211018836e+03
//           , 1.4887231232283756582e+03
//           , 9.0593769594993125859e+01
//           , 1.0
//         };
//         T y = T(8)/x;
//         T y2 = sqr(y);
//         T rc = evaluate_rational(PC, QC, y2);//horner( y2, PC)/ horner( y2, QC);
//         T rs = evaluate_rational(PS, QS, y2);//horner( y2, PS)/ horner( y2, QS);
//         T factor = rsqrt(Pi*x);
//         //
//         // The following code is really just:
//         //
//         // T z = x - 0.25f * Pi
//         // value = factor * (rc * sin(z) + y * rs * cos(z));
//         //
//         // But using the sin/cos addition formulae and constant values for
//         // sin/cos of PI/4 which then cancel part of the "factor" term as they're all
//         // 1 / sqrt(2):
//         //
//         auto [sx, cx] = sincos(x);
//         return factor*fma(y, rs * (cx + sx), rc * (sx - cx));
//       };
//        auto r = nan(as(x));
//       auto notdone = is_gez(x);

//       if( eve::any(notdone) )
//       {
//         notdone = next_interval(br_3,  notdone, x <= T(3), r, x);
//         if( eve::any(notdone) )
//         {
//           notdone = next_interval(br_5,  notdone, x <= T(5.5), r, x);
//           if( eve::any(notdone) )
//           {
//             notdone = next_interval(br_8,  notdone, x <= T(8), r, x);
//             if( eve::any(notdone) )
//             {
//               notdone = last_interval(br_large,  notdone, r, x);
//             }
//           }
//         }
//       }
//       r = if_else (is_eqz(x), minf(as(x)), r);
//       r = if_else (x == inf(as(x)), zero, r);
//       return r;
//     }
//     else return apply_over(cyl_bessel_y0, x);
//   }
}
