//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/bessel/detail/evaluate_rational.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/poleval.hpp>
#include <eve/module/math.hpp>

#include <array>

namespace eve::detail
{
template<floating_real_value T>
EVE_FORCEINLINE T
cyl_bessel_j0_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  using elt_t = element_type_t<T>;
  if constexpr( has_native_abi_v<T> )
  {
    auto x        = eve::abs(a0);
    auto br_large = [](auto x) // TODO a speedier float version
    {
      constexpr std::array<elt_t, 6> PC     = {2.2779090197304684302e+04,
                                               4.1345386639580765797e+04,
                                               2.1170523380864944322e+04,
                                               3.4806486443249270347e+03,
                                               1.5376201909008354296e+02,
                                               8.8961548424210455236e-01};
      constexpr std::array<elt_t, 6> QC     = {2.2779090197304684318e+04,
                                               4.1370412495510416640e+04,
                                               2.1215350561880115730e+04,
                                               3.5028735138235608207e+03,
                                               1.5711159858080893649e+02,
                                               1.0};
      constexpr std::array<elt_t, 6> PS     = {-8.9226600200800094098e+01,
                                               -1.8591953644342993800e+02,
                                               -1.1183429920482737611e+02,
                                               -2.2300261666214198472e+01,
                                               -1.2441026745835638459e+00,
                                               -8.8033303048680751817e-03};
      constexpr std::array<elt_t, 6> QS     = {5.7105024128512061905e+03,
                                               1.1951131543434613647e+04,
                                               7.2642780169211018836e+03,
                                               1.4887231232283756582e+03,
                                               9.0593769594993125859e+01,
                                               1.0};
      T                              y      = 8 * rec(x);
      T                              y2     = sqr(y);
      auto                           rc     = evaluate_rational(PC, QC, y2);
      auto                           rs     = evaluate_rational(PS, QS, y2);
      auto                           factor = rsqrt(pi(as(x)) * x);
      auto [sx, cx]                         = sincos(x);
      auto value                            = factor * fnma(y, rs * (sx - cx), rc * (sx + cx));
      return value;
    };

    if constexpr( std::is_same_v<elt_t, float> )
    {
      auto br_2 = [](auto x)
      {
        const T z = sqr(x);
        return (z - 5.7831859588623046875E0f) * // Ieee_constant<T,0x40b90fdc> ())*
               horn<T, 0xbe3110a6, 0x3c5a6271, 0xb9d01fb1, 0x36d660a0, 0xb382511c>(z);
      };

      auto br_8 = [](auto x)
      {
        auto q  = rec(x);
        auto w  = sqrt(q);
        auto p3 = w
                  * horn<T,
                         0x3f4c422a,
                         0xb6612dc2,
                         0xbd4b8bc1,
                         0xbb69539e,
                         0x3df54214,
                         0xbe5ba616,
                         0x3e3ef887,
                         0xbd8c100e>(q);
        w       = sqr(q);
        auto xn = q
                      * horn<T,
                             0xbdffff97,
                             0x3d84ed6e,
                             0xbe46a57f,
                             0x3f8040aa,
                             0xc09f3306,
                             0x418c7f6a,
                             0xc2113945,
                             0x4201aee0>(w)
                  - pio_4(as(w));
        return if_else(x == inf(as(x)), zero, p3 * cos(xn + x));
      };
      if constexpr( scalar_value<T> )
      {
        if( x == 0 ) return one(as(x));           // x is 0
        if( x == inf(as(x)) ) return zero(as(x)); // x is infinite
        if( is_nan(x) ) return x;                 // x is nan
        if( x < 2 ) return br_2(x);               // x in (0, 2]
        else if( x < 8 ) return br_8(x);          // x in (2, 8]
        return br_large(x);                       // x in (8, \infty)
      }
      else
      {
        if constexpr( has_native_abi_v<T> )
        {
          auto r       = nan(as(x));
          auto notdone = is_gez(x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_2, notdone, x <= T(2), r, x);
            if( eve::any(notdone) )
            {
              notdone = next_interval(br_8, notdone, x <= T(8), r, x);
              if( eve::any(notdone) ) { notdone = last_interval(br_large, notdone, r, x); }
            }
          }
          r = if_else(is_eqz(x), one(as(x)), r);
          r = if_else(x == inf(as(x)), zero, r);
          return r;
        }
        else return apply_over(cyl_bessel_j0, x);
      }
    }
    else
    {
      auto br_5 = [](auto x)
      {
        auto z    = sqr(x);
        auto xsml = x < T(1.0e-5);
        if( eve::all(xsml) ) return oneminus(z / 4);

        double DR1 = 5.78318596294678452118E0;
        double DR2 = 3.04712623436620863991E1;

        std::array<double, 4> RP = {
            -4.79443220978201773821E9,
            1.95617491946556577543E12,
            -2.49248344360967716204E14,
            9.70862251047306323952E15,
        };
        std::array<double, 8> RQ = {
            // 1.00000000000000000000E0,
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
        p *= poleval(z, RP) / poleval1(z, RQ);
        return p;
      };

      auto br_8 = [](auto x)
      {
        std::array<double, 7> PP = {7.96936729297347051624E-4,
                                    8.28352392107440799803E-2,
                                    1.23953371646414299388E0,
                                    5.44725003058768775090E0,
                                    8.74716500199817011941E0,
                                    5.30324038235394892183E0,
                                    9.99999999999999997821E-1};
        std::array<double, 7> PQ = {
            9.24408810558863637013E-4,
            8.56288474354474431428E-2,
            1.25352743901058953537E0,
            5.47097740330417105182E0,
            8.76190883237069594232E0,
            5.30605288235394617618E0,
            1.00000000000000000218E0,
        };
        std::array<double, 8> QP = {
            -1.13663838898469149931E-2,
            -1.28252718670509318512E0,
            -1.95539544257735972385E1,
            -9.32060152123768231369E1,
            -1.77681167980488050595E2,
            -1.47077505154951170175E2,
            -5.14105326766599330220E1,
            -6.05014350600728481186E0,
        };
        std::array<double, 7> QQ = {
            //      1.00000000000000000000E0,
            6.43178256118178023184E1,
            8.56430025976980587198E2,
            3.88240183605401609683E3,
            7.24046774195652478189E3,
            5.93072701187316984827E3,
            2.06209331660327847417E3,
            2.42005740240291393179E2,
        };
        auto w                  = 5.0 * rec(x);
        auto q                  = sqr(w);
        auto p                  = poleval(q, PP) / poleval(q, PQ);
        q                       = poleval(q, QP) / poleval1(q, QQ);
        auto xn                 = x - pio_4(as(x));
        auto [s, c]             = sincos(xn);
        p                       = fms(p, c, w * q * s);
        constexpr double sq2opi = .79788456080286535588;
        return p * sq2opi * rsqrt(x);
      };
      if constexpr( scalar_value<T> )
      {
        if( x == 0 ) return one(as(x));           // x is 0
        if( x == inf(as(x)) ) return zero(as(x)); // x is infinite
        if( is_nan(x) ) return x;                 // x is nan
        if( x < 5 ) return br_5(x);               // x in (0, 5]
        if( x < 8 ) return br_8(x);               // x in (5, 8]
        return br_large(x);                       // x in (8, \infty)
      }
      else
      {
        auto r       = nan(as(x));
        auto notdone = is_gez(x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(br_5, notdone, x <= T(5), r, x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_8, notdone, x <= T(8), r, x);
            if( eve::any(notdone) ) { notdone = last_interval(br_large, notdone, r, x); }
          }
        }
        r = if_else(is_eqz(x), one(as(x)), r);
        r = if_else(x == inf(as(x)), zero, r);
        return r;
      }
    }
  }
  else return apply_over(cyl_bessel_j0, a0);
}
}
