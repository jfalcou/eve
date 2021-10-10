//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <array>
#include <eve/module/real/special/detail/evaluate_rational.hpp>

namespace eve::detail
{
   template<floating_real_value T>
  EVE_FORCEINLINE T cyl_bessel_j1_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    // ensure x > 0 j0 is an even function
    using elt_t =  element_type_t<T>;
    auto s = if_else(is_negative(x), mone, one(as(x)));
    x = eve::abs(x);
    auto br_4 =  [](auto x) // x < 4
      {
        constexpr std::array<elt_t, 7> P1 = {
          -1.4258509801366645672e+11
          ,  6.6781041261492395835e+09
          , -1.1548696764841276794e+08
          ,  9.8062904098958257677e+05
          , -4.4615792982775076130e+03
          ,  1.0650724020080236441e+01
          , -1.0767857011487300348e-02
        };
        constexpr std::array<elt_t, 7> Q1 = {
          4.1868604460820175290e+12
          , 4.2091902282580133541e+10
          , 2.0228375140097033958e+08
          , 5.9117614494174794095e+05
          , 1.0742272239517380498e+03
          , 1.0
          , 0.0
        };
        constexpr elt_t x1(3.8317059702075123156e+00);
        constexpr elt_t x11(9.810e+02);
        constexpr elt_t x12(-3.2527979248768438556e-04);
        auto y =  sqr(x);
        auto r = evaluate_rational(P1, Q1, y);
        auto factor = x * (x + x1) * ((x - x11/256) - x12);
        auto value = factor * r;
        return value;
      };
    auto br_8 =  [](auto x) // x < 4
      {
        constexpr std::array<elt_t, 8> P2 = {
          -1.7527881995806511112e+16
          ,  1.6608531731299018674e+15
          , -3.6658018905416665164e+13
          ,  3.5580665670910619166e+11
          , -1.8113931269860667829e+09
          ,  5.0793266148011179143e+06
          , -7.5023342220781607561e+03
          ,  4.6179191852758252278e+00
        };
        constexpr std::array<elt_t, 8> Q2 = {
          1.7253905888447681194e+18
          , 1.7128800897135812012e+16
          , 8.4899346165481429307e+13
          , 2.7622777286244082666e+11
          , 6.4872502899596389593e+08
          , 1.1267125065029138050e+06
          , 1.3886978985861357615e+03
          , 1.0
        };
        constexpr elt_t x2(7.0155866698156187535e+00);
        constexpr elt_t x21(1.7960e+03);
        constexpr elt_t x22(-3.8330184381246462950e-05);
        auto y = sqr(x);
        auto r = evaluate_rational(P2, Q2, y);
        auto factor = x * (x + x2) * ((x - x21/256) - x22);
        auto value = factor * r;
        return value;
      };
    auto br_large =  [](auto x) // x < 4
      {
        constexpr std::array<elt_t, 7> PC = {
          -4.4357578167941278571e+06
          , -9.9422465050776411957e+06
          , -6.6033732483649391093e+06
          , -1.5235293511811373833e+06
          , -1.0982405543459346727e+05
          , -1.6116166443246101165e+03
          , 0.0
        };
        constexpr std::array<elt_t, 7> QC = {
          -4.4357578167941278568e+06
          , -9.9341243899345856590e+06
          , -6.5853394797230870728e+06
          , -1.5118095066341608816e+06
          , -1.0726385991103820119e+05
          , -1.4550094401904961825e+03
          , 1.0
        };
        constexpr std::array<elt_t, 7> PS = {
          3.3220913409857223519e+04
          , 8.5145160675335701966e+04
          , 6.6178836581270835179e+04
          , 1.8494262873223866797e+04
          , 1.7063754290207680021e+03
          , 3.5265133846636032186e+01
          , 0.0
        };
        constexpr std::array<elt_t, 7> QS = {
          7.0871281941028743574e+05
          , 1.8194580422439972989e+06
          , 1.4194606696037208929e+06
          , 4.0029443582266975117e+05
          , 3.7890229745772202641e+04
          , 8.6383677696049909675e+02
          , 1.0
        };
        T y = 8*rec(x);
        T y2 = sqr(y);
        auto rc = evaluate_rational(PC, QC, y2);
        auto rs = evaluate_rational(PS, QS, y2);
        auto factor = rsqrt(pi(as(x))*x);
        auto [sx, cx] = sincos(x);
        auto value = factor * fma(y,  rs*(sx+cx), rc*(sx-cx));
        return value;
      };

    using elt_t =  element_type_t<T>;
    if constexpr(scalar_value<T>)
    {
      if (x == 0)          return s*zero(as(x));  // x is 0
      if (x == inf(as(x))) return s*zero(as(x));    // x is infinite
      if (is_nan(x))       return x;              // x is nan
      if (x <= 4)          return s*br_4(x);      // x in (0, 4]
      if (x <= 8.0)        return s*br_8(x);      // x in (4, 8]
      return s*br_large(x);                         // x in (8, \infty)
    }
    else //simd
    {
      if constexpr(has_native_abi_v<T>)
      {
        auto r = nan(as(x));
        auto notdone = is_gez(x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_4,  notdone, x <= T(4), r, x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_8,  notdone, x <= T(8), r, x);
            if( eve::any(notdone) )
            {
              notdone = last_interval(br_large,  notdone, r, x);
            }
          }
        }
        r = if_else (is_eqz(x), zero(as(x)), r);
        r = if_else ((x == inf(as(x))), zero(as(x)), r);
        return s*r;
      }
      else return apply_over(cyl_bessel_j1, x);
    }
  }


//   template<floating_real_value T>
//   EVE_FORCEINLINE T cyl_bessel_j1_(EVE_SUPPORTS(cpu_), T a0) noexcept
//   {
//     using elt_t =  element_type_t<T>;
//     if constexpr( has_native_abi_v<T> )
//     {
//       auto x = eve::abs(a0);
//       if constexpr(std::is_same_v<elt_t, float>)
//       {
//         auto branch1 =  [](auto x){
//           const T z = sqr(x);
//           std::array < elt_t, 5> JP = {
//             -4.878788132172128E-009f,
//             6.009061827883699E-007f,
//             -4.541343896997497E-005f,
//             1.937383947804541E-003f,
//             -3.405537384615824E-002f
//           };

//           return (z- 1.46819706421238932572E1f)*x*poleval(z, JP);
//         };

//         auto branch2 =  [](auto x){
//           auto q = rec(x);
//           auto w = sqrt(q);
//          std::array < elt_t, 8> MO1 = {
//             6.913942741265801E-002f,
//             -2.284801500053359E-001f,
//             3.138238455499697E-001f,
//             -2.102302420403875E-001f,
//             5.435364690523026E-003f,
//             1.493389585089498E-001f,
//             4.976029650847191E-006f,
//             7.978845453073848E-001f
//           };
//           constexpr auto thpio4f =  2.35619449019234492885f;    /* 3*pi/4 */
//           std::array < elt_t, 8> PH1 = {
//             -4.497014141919556E+001f,
//             5.073465654089319E+001f,
//             -2.485774108720340E+001f,
//             7.222973196770240E+000f,
//             -1.544842782180211E+000f,
//             3.503787691653334E-001f,
//             -1.637986776941202E-001f,
//             3.749989509080821E-001f
//           };
//           auto p = w * poleval( q, MO1);
//           w = sqr(q);
//           auto xn = q * poleval( w, PH1) - thpio4f;
//           return  if_else(x == inf(as(x)), zero, p * cos(xn + x));
//         };

//         auto xlt2 = x < T(2);
//         if (eve::all(xlt2))        return branch1(x);
//         else if (none(xlt2))  return branch2(x);
//         else                  return if_else(xlt2, branch1(x), branch2(x));
//       }
//       else
//       {
//         auto branch1 =  [](auto x){
//           std::array <elt_t, 4> RP = {
//             -8.99971225705559398224E8,
//             4.52228297998194034323E11,
//             -7.27494245221818276015E13,
//             3.68295732863852883286E15,
//           };
//           std::array <elt_t, 8> RQ = {
//             /* 1.00000000000000000000E0,*/
//             6.20836478118054335476E2,
//             2.56987256757748830383E5,
//             8.35146791431949253037E7,
//             2.21511595479792499675E10,
//             4.74914122079991414898E12,
//             7.84369607876235854894E14,
//             8.95222336184627338078E16,
//             5.32278620332680085395E18,
//           };
//           auto z = sqr(x);
//           auto w = poleval(z, RP) / poleval1(z, RQ);
//           elt_t Z1 = 1.46819706421238932572E1;
//           elt_t Z2 = 4.92184563216946036703E1;
//           return w * x * (z - Z1) * (z - Z2);
//         };

//         auto branch2 =  [](auto x){
//           std::array <elt_t, 7> PP = {
//             7.62125616208173112003E-4,
//             7.31397056940917570436E-2,
//             1.12719608129684925192E0,
//             5.11207951146807644818E0,
//             8.42404590141772420927E0,
//             5.21451598682361504063E0,
//             1.00000000000000000254E0,
//           };
//           std::array <elt_t, 7>  PQ = {
//             5.71323128072548699714E-4,
//             6.88455908754495404082E-2,
//             1.10514232634061696926E0,
//             5.07386386128601488557E0,
//             8.39985554327604159757E0,
//             5.20982848682361821619E0,
//             9.99999999999999997461E-1,
//           };

//           std::array <elt_t, 8> QP = {
//             5.10862594750176621635E-2,
//             4.98213872951233449420E0,
//             7.58238284132545283818E1,
//             3.66779609360150777800E2,
//             7.10856304998926107277E2,
//             5.97489612400613639965E2,
//             2.11688757100572135698E2,
//             2.52070205858023719784E1,
//           };
//           std::array <elt_t, 7> QQ = {
//             /* 1.00000000000000000000E0,*/
//             7.42373277035675149943E1,
//             1.05644886038262816351E3,
//             4.98641058337653607651E3,
//             9.56231892404756170795E3,
//             7.99704160447350683650E3,
//             2.82619278517639096600E3,
//             3.36093607810698293419E2,
//           };

//           auto w = 5.0*rec(x);
//           auto z = sqr(w);
//           auto p = poleval(z, PP)/poleval(z, PQ);
//           auto q = poleval(z, QP)/poleval1(z, QQ);
//           constexpr auto thpio4 = 2.35619449019234492885;    /* 3*pi/4 */
//           auto xn = x - thpio4;
//           auto [sxn,  cxn] = sincos(xn);
//           p = fms(p, cxn, w * q * sxn);
//           auto sq2opi = T(.79788456080286535588);
//           return if_else(x == inf(as(x)), zero, p * sq2opi*rsqrt(x)) ;
//         };

//         auto xlt5 = x < T(5);
//         if (eve::all(xlt5))        return branch1(x);
//         else if (none(xlt5))  return branch2(x);
//         else                  return if_else(xlt5, branch1(x), branch2(x));
//       }
//     }
//     else
//       return apply_over(cyl_bessel_j1, a0);
//   }
}
