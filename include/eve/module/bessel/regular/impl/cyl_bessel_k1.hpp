//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/hz_device.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/horner.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <array>
#include <eve/module/bessel/detail/evaluate_rational.hpp>
#
namespace eve::detail
{
 template<floating_real_value T>
  EVE_FORCEINLINE T cyl_bessel_k1_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      auto br_1 =  [](auto x) // 0 1
        {
          if constexpr(std::same_as<elt_t, float>)
          {
            T y(8.695471287e-02f);
            constexpr std::array<elt_t, 3> P = {
              -3.621379531e-03f,
              7.131781976e-03f,
              -1.535278300e-05f
            };
            constexpr std::array<elt_t, 3> Q = {
              1.000000000e+00f,
              -5.173102701e-02f,
              9.203530671e-04f
            };
            T a = sqr(x/2);
            a = ((evaluate_rational(P, Q, a) + y) * sqr(a) + a / 2 + 1) * x / 2;
            constexpr std::array<elt_t, 5> P2 = {
              -3.079657469e-01f,
              -8.537108913e-02f,
              -4.640275408e-03f,
              -1.156442414e-04f
            };
            return reverse_horner(sqr(x), P2)*x +rec(x) + log(x) * a;
          }
          else
          {
            T y(8.69547128677368164e-02 );
            constexpr std::array<elt_t, 5> P =
            {
              -3.62137953440350228e-03,
              7.11842087490330300e-03,
              1.00302560256614306e-05,
              1.77231085381040811e-06
            };
            constexpr std::array<elt_t, 4> Q =
            {
              1.00000000000000000e+00,
              -4.80414794429043831e-02,
              9.85972641934416525e-04,
              -8.91196859397070326e-06
            };

            T a = sqr(x/2);
            a = ((evaluate_rational(P, Q, a) + y) * sqr(a) + a / 2 + 1) * x / 2;


            constexpr std::array<elt_t, 4> P2 =
            {
              -3.07965757829206184e-01,
              -7.80929703673074907e-02,
              -2.70619343754051620e-03,
              -2.49549522229072008e-05
            };
            constexpr std::array<elt_t, 4> Q2 =
            {
              1.00000000000000000e+00,
              -2.36316836412163098e-02,
              2.64524577525962719e-04,
              -1.49749618004162787e-06
            };
            return evaluate_rational(P2, Q2, sqr(x)) * x + rec(x) + log(x) * a;
          }
        };

      auto br_large =  [](auto x) // 1 infty
        {
          if constexpr(std::same_as<elt_t, float>)
          {
            auto y(1.450342178f);
            constexpr std::array<elt_t, 4> P = {
              -1.970280088e-01f,
              2.188747807e-02f,
              7.270394756e-01f,
              2.490678196e-01f
            };
            constexpr std::array<elt_t, 4> Q = {
              1.000000000e+00f,
              2.274292882e+00f,
              9.904984851e-01f,
              4.585534549e-02f
            };
            auto r = rec(x);
            if(eve::all(x < maxlog(as(x))))
              return ((evaluate_rational(P, Q, r)+y) * exp(-x)*rsqrt(x));
            else
            {
              T ex = exp(-x / 2);
              return ((evaluate_rational(P, Q, r)+y) * ex*rsqrt(x)) * ex;
            }
          }
          else
          {
           auto y(1.45034217834472656);
            constexpr std::array<elt_t, 9> P =
            {
              -1.97028041029226295e-01,
              -2.32408961548087617e+00,
              -7.98269784507699938e+00,
              -2.39968410774221632e+00,
              3.28314043780858713e+01,
              5.67713761158496058e+01,
              3.30907788466509823e+01,
              6.62582288933739787e+00,
              3.08851840645286691e-01
            };
           constexpr std::array<elt_t, 9> Q =
            {
              1.00000000000000000e+00,
              1.41811409298826118e+01,
              7.35979466317556420e+01,
              1.77821793937080859e+02,
              2.11014501598705982e+02,
              1.19425262951064454e+02,
              2.88448064302447607e+01,
              2.27912927104139732e+00,
              2.50358186953478678e-02
            };
            auto r = rec(x);
            if(eve::all(x < maxlog(as(x))))
              return ((evaluate_rational(P, Q, r)+y) * exp(-x)*rsqrt(x));
            else
            {
              T ex = exp(-x / 2);
              return ((evaluate_rational(P, Q, r)+y) * ex*rsqrt(x)) * ex;
            }
          }
        };

      if constexpr(scalar_value<T>)
      {
        if (is_ngez(x))      return nan(as(x));
        if (x == 0)          return inf(as(x));  // x is 0
        if (x == inf(as(x))) return zero(as(x)); // x is infinite
        if (x < one(as(x)))  return br_1(x);     // x in (0, 1]
        return br_large(x);                      // x in (t1, \infty)
      }
      else
      {
        if constexpr(has_native_abi_v<T>)
        {
          auto r = nan(as(x));
          auto notdone = is_gtz(x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_1,  notdone, x <= T(1), r, x);
            if( eve::any(notdone) )
            {
              notdone = last_interval(br_large,  notdone, r, x);
            }
          }
          r = if_else (is_eqz(x), inf(as(x)), r);
          r = if_else (x == inf(as(x)), zero, r);
          return r;
        }
      }
    }
    else return apply_over(cyl_bessel_k1, x);
  }
}
