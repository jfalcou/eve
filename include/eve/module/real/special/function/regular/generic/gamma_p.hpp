//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/epsilon.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/lgamma.hpp>
#include <eve/function/log.hpp>
#include <eve/function/max.hpp>
#include <eve/function/maximum.hpp>
#include <eve/function/min.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

namespace eve::detail
{

  template<floating_value T, floating_value U>
  EVE_FORCEINLINE  auto gamma_p_(EVE_SUPPORTS(cpu_)
                              , T a
                              , U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(gamma_p, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T gamma_p_(EVE_SUPPORTS(cpu_), T x, T a) noexcept
  requires has_native_abi_v<T>
  {
    auto const third = T(1/3.0);
    auto res = nan(as<T>()); //nan case treated here
    auto notdone =  is_not_nan(x);
    const auto amax = T(1048576);
    auto test = (a > amax);
    if (eve::any(test))
    {
      auto z = eve::fma( 1024*rsqrt(a), x-(a-third), amax-third);
      x =  eve::max(z, zero(as(x)));
      a =  if_else(test, amax, a);
    }
    auto lginc = [](auto a0,  auto a1,  auto test){
      // insure convergence in each case for all members of simd vector
      // making x = a+1 when the test do not succeed
      auto x = if_else(test, a0, a1);

      //Series expansion for x < a+1
      auto ap  = a1;
      auto del = one(as(ap));
      auto sum = del;

      while ( eve::any(abs(del) >=  T(100)*epsilon(maximum(abs(sum)))))
      {
        ap  += one(as(ap));
        del  = x*del/ap;
        sum += del;
     }
      auto b = sum*eve::exp(fms(a1, eve::log(x), eve::lgamma(inc(a1))+x));
      //  For very small a, the series may overshoot very slightly.
      b = eve::min(b, one(as(b)));
      //  if lower, b(k) = bk; else b(k) = 1-bk; end
      return if_else(is_eqz(a0) && is_eqz(a1), one, b);
    };
    auto uginc = [](auto x,  auto a, auto test){
      // insure convergence in each case for all members of simd vector
      // making x =  a <  a+1 when the test do not succeed
      x = if_else(test, x, inc(a));
      // Continued fraction for x >= a+1
      //k = find(a ~= 0 & x >= a+1); % & x ~= 0
      auto x0 = one(as(x));
      auto x1 = x;
      auto b0 = zero(as(x));
      auto b1 = x0;
      auto fac = rec(x1);
      auto n =  one(as(x));
      auto g = b1*fac;
      auto gold = b0;

      while (   maximum(abs(g-gold))  >=  100*eve::epsilon(maximum(eve::abs(g))))
      {
        gold = g;
        auto ana = n - a;
        x0 = fma(x0, ana, x1)* fac;
        b0 = fma(b0, ana, b1)* fac;
        auto anf = n*fac;
        x1 = fma(x, x0, anf * x1);
        b1 = fma(x, b0, anf * b1);
        fac = rec(x1);
        g = b1 * fac;
        n = inc(n);
      }
      return if_else( eve::is_infinite(x)
                    , one, oneminus(exp(-x+a*log(x)- lgamma(a))*g));
    };

    test = x < inc(a);
    notdone = next_interval(lginc, notdone, test, res, x, a, test);
    if (eve::any(notdone)) last_interval(uginc, notdone, res, x, a, !test);
    return res;
  }
}
