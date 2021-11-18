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
#include <eve/function/cos.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/horner.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqr.hpp>
#include <array>
#include <eve/module/real/special/detail/evaluate_rational.hpp>
#include <eve/module/real/core/detail/generic/poleval.hpp>

namespace eve::detail
{
 template<floating_real_value T>
  EVE_FORCEINLINE T cyl_bessel_i1_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      auto br_7_75 =  [](auto x)
        {
          if constexpr(std::same_as<elt_t, float>)
          {
            constexpr std::array<elt_t, 8> P = {
              8.333333221e-02f,
              6.944453712e-03f,
              3.472097211e-04f,
              1.158047174e-05f,
              2.739745142e-07f,
              5.135884609e-09f,
              5.262251502e-11f,
              1.331933703e-12f
            };
            T xo_2 = x/2;
            T a = sqr(xo_2);
            T r = reverse_horner(a, 1.0f, 0.5f, reverse_horner(a, P));
            return xo_2*r; ;
          }
          else
          {
            constexpr std::array<elt_t, 13> P = {
              8.333333333333333803e-02,
              6.944444444444341983e-03,
              3.472222222225921045e-04,
              1.157407407354987232e-05,
              2.755731926254790268e-07,
              4.920949692800671435e-09,
              6.834657311305621830e-11,
              7.593969849687574339e-13,
              6.904822652741917551e-15,
              5.220157095351373194e-17,
              3.410720494727771276e-19,
              1.625212890947171108e-21,
              1.332898928162290861e-23
            };
            T xo_2 = x/2;
            T a = sqr(xo_2);
            T r = reverse_horner(a, 1.0, 0.5, reverse_horner(a, P));
            return xo_2*r; ;
          }
        };

      auto br_medium =  [](auto x) //float inf double 500
        {
          if constexpr(std::same_as<elt_t, float>)
          {
            constexpr std::array<elt_t, 5> P = {
              3.98942115977513013e-01f,
              -1.49581264836620262e-01f,
              -4.76475741878486795e-02f,
              -2.65157315524784407e-02f,
              -1.47148600683672014e-01f
            };
            auto ex = eve::exp(x/2);
            return ex*(ex*reverse_horner(rec(x), P)*rsqrt(x));
          }
          else
          {
            constexpr std::array<elt_t, 22> P = {
              3.989422804014406054e-01,
              -1.496033551613111533e-01,
              -4.675104253598537322e-02,
              -4.090895951581637791e-02,
              -5.719036414430205390e-02,
              -1.528189554374492735e-01,
              3.458284470977172076e+00,
              -2.426181371595021021e+02,
              1.178785865993440669e+04,
              -4.404655582443487334e+05,
              1.277677779341446497e+07,
              -2.903390398236656519e+08,
              5.192386898222206474e+09,
              -7.313784438967834057e+10,
              8.087824484994859552e+11,
              -6.967602516005787001e+12,
              4.614040809616582764e+13,
              -2.298849639457172489e+14,
              8.325554073334618015e+14,
              -2.067285045778906105e+15,
              3.146401654361325073e+15,
              -2.213318202179221945e+15
            };
            return eve::exp(x) * reverse_horner(rec(x), P)*eve::rsqrt(x);
          }
        };

      auto br_large =  [](auto x)
        {
          if constexpr(std::same_as<elt_t, double>)
          {
            constexpr std::array<elt_t, 5> P = {
              3.989422804014314820e-01,
              -1.496033551467584157e-01,
              -4.675105322571775911e-02,
              -4.090421597376992892e-02,
              -5.843630344778927582e-02
            };
            auto ex = eve::exp(x/2);
            return ex * (ex * reverse_horner(rec(x), P) / eve::sqrt(x));
          }
          else
          {
            return inf(as(x));
          }
        };

      if constexpr(scalar_value<T>)
      {
        if (is_ngez(x))      return nan(as(x));
        if (x == 0)          return zero(as(x)); // x is 0
        if (x == inf(as(x))) return inf(as(x));  // x is infinite
        if (x < T(7.75))     return br_7_75(x);  // x in (0, 7.75]
        const auto thresh = if_else(std::same_as < elt_t, double>, elt_t(500), inf(as<elt_t>()));
        if (x < thresh)      return br_medium(x);// x in (7.75, thresh]
        return br_large(x);                      // x in (thresh, \infty)
      }
      else
      {
        if constexpr(has_native_abi_v<T>)
        {
          auto r = nan(as(x));
          auto notdone = is_gtz(x);
          if( eve::any(notdone) )
          {
            notdone = next_interval(br_7_75,  notdone, x <= T(7.75), r, x);
            if( eve::any(notdone) )
            {
              const auto thresh = if_else(std::same_as < elt_t, float>, elt_t(500), inf(as<elt_t>()));
              notdone = next_interval(br_medium,  notdone, x <= T(thresh), r, x);
              if( eve::any(notdone) )
              {
                notdone = last_interval(br_large,  notdone, r, x);
              }
            }
          }
          r = if_else (is_eqz(x), zero(as(x)), r);
          r = if_else (x == inf(as(x)), inf, r);
          return r;
        }
      }
    }
    else return apply_over(cyl_bessel_i1, x);
  }
}
