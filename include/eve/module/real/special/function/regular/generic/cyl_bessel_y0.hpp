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
#include <eve/function/if_else.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/cyl_bessel_j0.hpp>
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
#include <type_traits>
#include <eve/module/real/core/detail/generic/poleval.hpp>

namespace eve::detail
{
//  *             cyl_bessel_y0()
//  * Bessel function of second kind, order zero  */
//  * Rational approximation coefficients YP[] are used for x < 6.5.
//  * The function computed is  cyl_bessel_y0(x)  -  2 ln(x) j0(x) / pi,
//  * whose value at x = 0 is  2 * ( log(0.5) + EUL ) / pi
//  * = 0.073804295108687225 , EUL is Euler's constant.

  template<floating_real_value T>
  EVE_FORCEINLINE T cyl_bessel_y0_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto branch1 =  [](auto x){
          std::array<elt_t, 5> YP = {
            9.454583683980369E-008f,
            -9.413212653797057E-006f,
            5.344486707214273E-004f,
            -1.584289289821316E-002f,
            1.707584643733568E-001f
          };
          constexpr elt_t YZ1 =  0.43221455686510834878f;
          const T z = sqr(x);
          auto w = (z-YZ1) * poleval( z, YP);
          return w + twoopi(as(x)) * log(x) *cyl_bessel_j0(x);
        };

        auto branch2 =  [](auto x){
          std::array<elt_t, 8> MO = {
            -6.838999669318810E-002f,
            1.864949361379502E-001f,
            -2.145007480346739E-001f,
            1.197549369473540E-001f,
            -3.560281861530129E-003f,
            -4.969382655296620E-002f,
            -3.355424622293709E-006f,
            7.978845717621440E-001f
          };
          std::array<elt_t, 8> PH = {
            3.242077816988247E+001f,
            -3.630592630518434E+001f,
            1.756221482109099E+001f,
            -4.974978466280903E+000f,
            1.001973420681837E+000f,
            -1.939906941791308E-001f,
            6.490598792654666E-002f,
            -1.249992184872738E-001f
          };
          auto q = rec(x);
          auto w = sqrt(q);
          auto p = w * poleval( q, MO);
          w = sqr(q);
          auto xn = fms(q, poleval( w, PH), pio_4(as(x)));
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
          std::array<elt_t, 8> YP = {
            1.55924367855235737965E4,
            -1.46639295903971606143E7,
            5.43526477051876500413E9,
            -9.82136065717911466409E11,
            8.75906394395366999549E13,
            -3.46628303384729719441E15,
            4.42733268572569800351E16,
            -1.84950800436986690637E16,
          };
          std::array<elt_t, 7> YQ = {
            /* 1.00000000000000000000E0,*/
            1.04128353664259848412E3,
            6.26107330137134956842E5,
            2.68919633393814121987E8,
            8.64002487103935000337E10,
            2.02979612750105546709E13,
            3.17157752842975028269E15,
            2.50596256172653059228E17,
          };
          const T z = sqr(x);
          auto w = poleval( z, YP)/ poleval( z, YQ);
          return w + twoopi(as(x)) * log(x) *cyl_bessel_j0(x);
        };

        auto branch2 =  [](auto x){
          std::array<elt_t, 7> PP = {
            7.96936729297347051624E-4,
            8.28352392107440799803E-2,
            1.23953371646414299388E0,
            5.44725003058768775090E0,
            8.74716500199817011941E0,
            5.30324038235394892183E0,
            9.99999999999999997821E-1,
          };
          std::array<elt_t, 7>  PQ = {
            9.24408810558863637013E-4,
            8.56288474354474431428E-2,
            1.25352743901058953537E0,
            5.47097740330417105182E0,
            8.76190883237069594232E0,
            5.30605288235394617618E0,
            1.00000000000000000218E0,
          };
          std::array<elt_t, 8>  QP = {
            -1.13663838898469149931E-2,
            -1.28252718670509318512E0,
            -1.95539544257735972385E1,
            -9.32060152123768231369E1,
            -1.77681167980488050595E2,
            -1.47077505154951170175E2,
            -5.14105326766599330220E1,
            -6.05014350600728481186E0,
          };
          std::array<elt_t, 7> QQ = {
            /*  1.00000000000000000000E0,*/
            6.43178256118178023184E1,
            8.56430025976980587198E2,
            3.88240183605401609683E3,
            7.24046774195652478189E3,
            5.93072701187316984827E3,
            2.06209331660327847417E3,
            2.42005740240291393179E2,
          };

          auto  w = 5.0*rec(x);
          auto  z = sqr(w);
          auto  p = poleval( z, PP)/poleval( z, PQ );
          auto  q = poleval( z, QP)/poleval1( z, QQ );
          auto [s, c] = sincos(x);
          p =  fma(w, q, p)*s +fms(w, q, p)*c;
          return if_else(is_infinite(x), zero, p*rsqrt(x*pi(as(x))));
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
      return apply_over(cyl_bessel_y0, a0);
  }
}
