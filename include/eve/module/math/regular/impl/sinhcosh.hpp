//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/arithmetic/regular/is_positive.hpp> // SUPPRESS
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/expm1.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/module/math/detail/constant/rempio2_limits.hpp>
#include <eve/module/math/detail/generic/trig_finalize.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr kumi::tuple<T, T>
  sinhcosh_(EVE_SUPPORTS(cpu_) , T a0) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      //Ieee_constant<T,0x42B0C0A4U, 0x40862E42FEFA39EFULL>(); // 88.376251220703125f, 709.782712893384
      T ovflimit  =   maxlog(as<T>());
      auto      x = eve::abs(a0);

      if constexpr(scalar_value<T>)
      {
        if (x < T(0x1.0p-28)) return {a0, one(eve::as<T>())};
        auto h = (a0 > T(0)) ? T(1) : T(-1);
        if (x >= ovflimit)
        {
          auto w = exp(x*half(eve::as<T>()));
          auto t = half(eve::as<T>())*w;
          t *= w;
          return {t*h, t};
        }
        h*= half(eve::as<T>());
        auto t = expm1(x);
        auto inct = inc(t);
        auto u = t/inct;
        auto s = h*(fnma(t, u, t)+t);
        auto c = (x > T(22.0f)) ? inct*half(eve::as<T>()) : average(inct, rec(inct));
        return {s, c};       }
      else
      {
        auto h = if_else( is_positive(a0), one(eve::as<T>()), mone(eve::as<T>()));
        auto t = expm1(x);
        auto inct = inc(t);
        auto u = t/inct;
        auto z =  fnma(t, u, t);
        auto s = half(eve::as<T>())*h*(z+t);
        auto invt = if_else(x > T(22.0f), eve::zero, rec(inct));
        auto c = average(inct, invt);
        auto test = x <  ovflimit;
        if (eve::all(test)) return {s, c};

        auto w = exp(x*half(eve::as<T>()));
        t = half(eve::as<T>())*w;
        t *= w;

        s = if_else(test, s, t*h);
        c = if_else(test, c, t);
        return {s, c};
      }
    }
    else
    {
      return apply_over2(sinhcosh, a0);
    }
  }
}
