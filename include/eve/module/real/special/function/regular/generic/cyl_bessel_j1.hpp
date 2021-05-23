//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/all.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/none.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/invsqrt_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/module/real/core/detail/generic/poleval.hpp>
#include <type_traits>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE T cyl_bessel_j1_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      auto x = eve::abs(a0);
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto branch1 =  [](auto x){
          const T z = sqr(x);
          std::array < elt_t, 5> JP = {
            -4.878788132172128E-009f,
            6.009061827883699E-007f,
            -4.541343896997497E-005f,
            1.937383947804541E-003f,
            -3.405537384615824E-002f
          };

          return (z- 1.46819706421238932572E1f)*x*poleval(z, JP);
        };

        auto branch2 =  [](auto x){
          auto q = rec(x);
          auto w = sqrt(q);
         std::array < elt_t, 8> MO1 = {
            6.913942741265801E-002f,
            -2.284801500053359E-001f,
            3.138238455499697E-001f,
            -2.102302420403875E-001f,
            5.435364690523026E-003f,
            1.493389585089498E-001f,
            4.976029650847191E-006f,
            7.978845453073848E-001f
          };
          constexpr auto thpio4f =  2.35619449019234492885f;    /* 3*pi/4 */
          std::array < elt_t, 8> PH1 = {
            -4.497014141919556E+001f,
            5.073465654089319E+001f,
            -2.485774108720340E+001f,
            7.222973196770240E+000f,
            -1.544842782180211E+000f,
            3.503787691653334E-001f,
            -1.637986776941202E-001f,
            3.749989509080821E-001f
          };
          auto p = w * poleval( q, MO1);
          w = sqr(q);
          auto xn = q * poleval( w, PH1) - thpio4f;
          return  if_else(x == inf(as(x)), zero, p * cos(xn + x));
        };

        auto xlt2 = x < T(2);
        if (eve::all(xlt2))        return branch1(x);
        else if (none(xlt2))  return branch2(x);
        else                  return if_else(xlt2, branch1(x), branch2(x));
      }
      else
      {
        auto branch1 =  [](auto x){
          std::array <elt_t, 4> RP = {
            -8.99971225705559398224E8,
            4.52228297998194034323E11,
            -7.27494245221818276015E13,
            3.68295732863852883286E15,
          };
          std::array <elt_t, 8> RQ = {
            /* 1.00000000000000000000E0,*/
            6.20836478118054335476E2,
            2.56987256757748830383E5,
            8.35146791431949253037E7,
            2.21511595479792499675E10,
            4.74914122079991414898E12,
            7.84369607876235854894E14,
            8.95222336184627338078E16,
            5.32278620332680085395E18,
          };
          auto z = sqr(x);
          auto w = poleval(z, RP) / poleval1(z, RQ);
          elt_t Z1 = 1.46819706421238932572E1;
          elt_t Z2 = 4.92184563216946036703E1;
          return w * x * (z - Z1) * (z - Z2);
        };

        auto branch2 =  [](auto x){
          std::array <elt_t, 7> PP = {
            7.62125616208173112003E-4,
            7.31397056940917570436E-2,
            1.12719608129684925192E0,
            5.11207951146807644818E0,
            8.42404590141772420927E0,
            5.21451598682361504063E0,
            1.00000000000000000254E0,
          };
          std::array <elt_t, 7>  PQ = {
            5.71323128072548699714E-4,
            6.88455908754495404082E-2,
            1.10514232634061696926E0,
            5.07386386128601488557E0,
            8.39985554327604159757E0,
            5.20982848682361821619E0,
            9.99999999999999997461E-1,
          };

          std::array <elt_t, 8> QP = {
            5.10862594750176621635E-2,
            4.98213872951233449420E0,
            7.58238284132545283818E1,
            3.66779609360150777800E2,
            7.10856304998926107277E2,
            5.97489612400613639965E2,
            2.11688757100572135698E2,
            2.52070205858023719784E1,
          };
          std::array <elt_t, 7> QQ = {
            /* 1.00000000000000000000E0,*/
            7.42373277035675149943E1,
            1.05644886038262816351E3,
            4.98641058337653607651E3,
            9.56231892404756170795E3,
            7.99704160447350683650E3,
            2.82619278517639096600E3,
            3.36093607810698293419E2,
          };

          auto w = 5.0*rec(x);
          auto z = sqr(w);
          auto p = poleval(z, PP)/poleval(z, PQ);
          auto q = poleval(z, QP)/poleval1(z, QQ);
          constexpr auto thpio4 = 2.35619449019234492885;    /* 3*pi/4 */
          auto xn = x - thpio4;
          auto [sxn,  cxn] = sincos(xn);
          p = fms(p, cxn, w * q * sxn);
          auto sq2opi = T(.79788456080286535588);
          return if_else(x == inf(as(x)), zero, p * sq2opi*rsqrt(x)) ;
        };

        auto xlt5 = x < T(5);
        if (eve::all(xlt5))        return branch1(x);
        else if (none(xlt5))  return branch2(x);
        else                  return if_else(xlt5, branch1(x), branch2(x));
      }
    }
    else
      return apply_over(cyl_bessel_j1, a0);
  }
}
