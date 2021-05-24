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
#include <eve/function/fms.hpp>
#include <eve/function/all.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/cyl_bessel_j1.hpp>
#include <eve/function/none.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sin.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/log.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/invsqrt_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/module/real/core/detail/generic/poleval.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T cyl_bessel_y1_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto branch1 =  [](auto x){
          std::array<elt_t, 5> YP = {
            8.061978323326852E-009f,
            -9.496460629917016E-007f,
            6.719543806674249E-005f,
            -2.641785726447862E-003f,
            4.202369946500099E-002f
          };
          constexpr elt_t Y01 = 4.66539330185668857532f;
          const T z = sqr(x);
          auto w = (z-Y01)*x*poleval( z, YP);
          w = fma(twoopi(as(x)), fms(log(x), cyl_bessel_j1(x), rec(x)), w);
          return if_else(is_eqz(x), minf(as(x)), w);
        };

        auto branch2 =  [](auto x){
          std::array<elt_t, 8> MO1 = {
            6.913942741265801E-002f,
            -2.284801500053359E-001f,
            3.138238455499697E-001f,
            -2.102302420403875E-001f,
            5.435364690523026E-003f,
            1.493389585089498E-001f,
            4.976029650847191E-006f,
            7.978845453073848E-001f
          };
          std::array<elt_t, 8> PH1 = {
            -4.497014141919556E+001f,
            5.073465654089319E+001f,
            -2.485774108720340E+001f,
            7.222973196770240E+000f,
            -1.544842782180211E+000f,
            3.503787691653334E-001f,
            -1.637986776941202E-001f,
            3.749989509080821E-001f
          };
          auto q = rec(x);
          auto w = sqrt(q);
          auto p = w * poleval( q, MO1);
          w = sqr(q);
          auto xn = fms(q, poleval( w, PH1), 3*pio_4(as(x)));
          return if_else(x == inf(as(x)), zero, p * sin(xn + x));
        };

        auto r = nan(as<T>()); //nan case treated here
        auto notdone =  is_nltz(a0);
        if(eve::any(notdone))
        {
          notdone = next_interval(branch1, notdone, a0 < T(2), r, a0);
          if (eve::any(notdone))
          {
            last_interval(branch2, notdone, r, a0);
          }
        }
        return r;
      }
      else // double
      {
        auto branch1 =  [](auto x){
          std::array<elt_t, 6> YP = {
            1.26320474790178026440E9,
            -6.47355876379160291031E11,
            1.14509511541823727583E14,
            -8.12770255501325109621E15,
            2.02439475713594898196E17,
            -7.78877196265950026825E17,
          };
          std::array<elt_t, 8> YQ = {
            /* 1.00000000000000000000E0,*/
            5.94301592346128195359E2,
            2.35564092943068577943E5,
            7.34811944459721705660E7,
            1.87601316108706159478E10,
            3.88231277496238566008E12,
            6.20557727146953693363E14,
            6.87141087355300489866E16,
            3.97270608116560655612E18,
          };
          const T z = sqr(x);
          auto w = x*poleval( z, YP)/poleval1( z, YQ);
          return if_else(is_eqz(x), minf(as(x))
                        , w + twoopi(as(x)) * fms(log(x), cyl_bessel_j1(x), rec(x)));
        };

        auto branch2 =  [](auto x){
          std::array<elt_t, 7> PP = {
            7.62125616208173112003E-4,
            7.31397056940917570436E-2,
            1.12719608129684925192E0,
            5.11207951146807644818E0,
            8.42404590141772420927E0,
            5.21451598682361504063E0,
            1.00000000000000000254E0,
          };
          std::array<elt_t, 7>  PQ = {
            5.71323128072548699714E-4,
            6.88455908754495404082E-2,
            1.10514232634061696926E0,
            5.07386386128601488557E0,
            8.39985554327604159757E0,
            5.20982848682361821619E0,
            9.99999999999999997461E-1,
          };
          std::array<elt_t, 8>  QP = {
            5.10862594750176621635E-2,
            4.98213872951233449420E0,
            7.58238284132545283818E1,
            3.66779609360150777800E2,
            7.10856304998926107277E2,
            5.97489612400613639965E2,
            2.11688757100572135698E2,
            2.52070205858023719784E1,
          };
          std::array<elt_t, 7> QQ = {
            /*  1.00000000000000000000E0,*/
            7.42373277035675149943E1,
            1.05644886038262816351E3,
            4.98641058337653607651E3,
            9.56231892404756170795E3,
            7.99704160447350683650E3,
            2.82619278517639096600E3,
            3.36093607810698293419E2,
          };

          auto  w = 5.0*rec(x);
          auto  z = sqr(w);
          auto  p = poleval( z, PP)/poleval( z, PQ );
          auto  q = poleval( z, QP)/poleval1( z, QQ );
          auto [s, c] = sincos(x);
          p =  fms(w, q, p)*s - fma(w, q, p)*c;
          p =  p*rsqrt(x*pi(as(x)));
          return if_else(is_infinite(x), zero, p);
        };

        auto r = nan(as<T>()); //nan case treated here
        auto notdone =  is_nltz(a0);
        if(eve::any(notdone))
        {
          notdone = next_interval(branch1, notdone, a0 < T(5), r, a0);
          if (eve::any(notdone))
          {
            last_interval(branch2, notdone, r, a0);
          }
        }
        return r;
      }
    }
    else
      return apply_over(cyl_bessel_y1, a0);
  }
}
