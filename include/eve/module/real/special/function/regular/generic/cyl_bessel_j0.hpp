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
#include <eve/function/is_infinite.hpp>
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
#include <eve/module/real/core/detail/generic/horn.hpp>
#include <eve/module/real/core/detail/generic/poleval.hpp>
#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T cyl_bessel_j0_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      auto x = eve::abs(a0);
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto branch1 =  [](auto x){
          const T z = sqr(x);
          return (z-5.7831859588623046875E0f)*    //Ieee_constant<T,0x40b90fdc> ())*
          horn<T,
          0xbe3110a6,
          0x3c5a6271,
          0xb9d01fb1,
          0x36d660a0,
          0xb382511c
          > (z);
        };

        auto branch2 =  [](auto x){
          auto q = rec(x);
          auto w = sqrt(q);
          auto p3 = w *
          horn<T,
          0x3f4c422a,
          0xb6612dc2,
          0xbd4b8bc1,
          0xbb69539e,
          0x3df54214,
          0xbe5ba616,
          0x3e3ef887,
          0xbd8c100e
          > (q);
          w = sqr(q);
          auto xn =  q*
          horn<T,
          0xbdffff97,
          0x3d84ed6e,
          0xbe46a57f,
          0x3f8040aa,
          0xc09f3306,
          0x418c7f6a,
          0xc2113945,
          0x4201aee0
          >(w)-pio_4(as(w));
          return if_else(x == inf(as(x)), zero, p3*cos(xn+x));
        };

        auto xlt2 = x < T(2);
        if (eve::all(xlt2))        return branch1(x);
        else if (none(xlt2))  return branch2(x);
        else                  return if_else(xlt2, branch1(x), branch2(x));
      }
      else
      {
        auto branch1 =  [](auto x){
          auto z = sqr(x);
//   if( x < 1.0e-5 )
//     return( 1.0 - z/4.0 );

          /*  5.783185962946784521175995758455807035071 */
          double DR1 = 5.78318596294678452118E0;
          /* 30.47126234366208639907816317502275584842 */
          double DR2 = 3.04712623436620863991E1;

          std::array<double, 4> RP = {
            -4.79443220978201773821E9,
            1.95617491946556577543E12,
            -2.49248344360967716204E14,
            9.70862251047306323952E15,
          };
          std::array<double, 8> RQ = {
//            1.00000000000000000000E0,
            4.99563147152651017219E2,
            1.73785401676374683123E5,
            4.84409658339962045305E7,
            1.11855537045356834862E10,
            2.11277520115489217587E12,
            3.10518229857422583814E14,
            3.18121955943204943306E16,
            1.71086294081043136091E18,
          };
          auto p = (z - DR1) * (z - DR2);
          p *=  poleval( z, RP)/poleval1( z, RQ);
          return p;
        };

        auto branch2 =  [](auto x){
          std::array < double, 7> PP = {
            7.96936729297347051624E-4,
            8.28352392107440799803E-2,
            1.23953371646414299388E0,
            5.44725003058768775090E0,
            8.74716500199817011941E0,
            5.30324038235394892183E0,
            9.99999999999999997821E-1
          };
          std::array < double, 7> PQ = {
            9.24408810558863637013E-4,
            8.56288474354474431428E-2,
            1.25352743901058953537E0,
            5.47097740330417105182E0,
            8.76190883237069594232E0,
            5.30605288235394617618E0,
            1.00000000000000000218E0,
          };
          std::array < double, 8> QP = {
            -1.13663838898469149931E-2,
            -1.28252718670509318512E0,
            -1.95539544257735972385E1,
            -9.32060152123768231369E1,
            -1.77681167980488050595E2,
            -1.47077505154951170175E2,
            -5.14105326766599330220E1,
            -6.05014350600728481186E0,
          };
          std::array < double, 7> QQ = {
//            1.00000000000000000000E0,
            6.43178256118178023184E1,
            8.56430025976980587198E2,
            3.88240183605401609683E3,
            7.24046774195652478189E3,
            5.93072701187316984827E3,
            2.06209331660327847417E3,
            2.42005740240291393179E2,
          };
          auto  w = 5.0*rec(x);
          auto  q = sqr(w);
          auto  p = poleval( q, PP)/poleval( q, PQ );
                q = poleval( q, QP)/poleval1( q, QQ );
          auto xn = x - pio_4(as(x));
          auto [s, c] = sincos(xn);
          p = fms(p, c, w*q*s);
          auto sq2opi = T(.79788456080286535588);
          return if_else(is_infinite(x), zero, p*sq2opi*rsqrt(x));
        };

        auto xlt5 = x < T(5);
        if (eve::all(xlt5))        return branch1(x);
        else if (none(xlt5))  return branch2(x);
        else                  return if_else(xlt5, branch1(x), branch2(x));
      }
    }
    else
      return apply_over(cyl_bessel_j0, a0);
  }
}
