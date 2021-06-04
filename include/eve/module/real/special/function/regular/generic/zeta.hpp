//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/tgamma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_nan.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/powm1.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/detail/hz_device.hpp>


namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE   auto zeta_(EVE_SUPPORTS(cpu_), T x, U y) noexcept
                ->  decltype(arithmetic_call(zeta, x, y))
  {
    return arithmetic_call(zeta, x, y);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE T zeta_(EVE_SUPPORTS(cpu_)
                              , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using elt_t = element_type_t<T>;
      //
      // This is algorithm 3 from:
      //
      // "An Efficient Algorithm for the Riemann Zeta Function", P. Borwein,
      // Canadian Mathematical Society, Conference Proceedings.
      // See: http://www.cecm.sfu.ca/personal/pborwein/PAPERS/P155.pdf
      //
      auto zetp = [](auto s)
        {
          auto sc = oneminus(s);
          const int n = if_else(sizeof(elt_t) == 8, 18, 7);
          auto sum(zero(as(s)));
          auto two_n = ldexp(T(1), n);
          auto ej_sign(one(as(s)));
          for(int j = 1; j <= n; ++j)
          {
            sum += ej_sign * -two_n*pow_abs(T(j), -s);
            ej_sign = -ej_sign;
          }
          auto ej_sum(one(as(s)));
          auto ej_term(one(as(s)));
          for(int j = n; j <= 2 * n - 1; ++j)
          {
            sum += ej_sign * (ej_sum - two_n) * pow_abs(T(inc(j)), -s);
            ej_sign = -ej_sign;
            ej_term *= 2 * n - j;
            ej_term /= j - n + 1;
            ej_sum += ej_term;
          }
          auto z = -sum/(two_n*(-powm1(T(2), sc)));
          return if_else(s == one(as(s)), allbits, z);
        };
      auto r = nan(as(x));
      auto notdone = x != one(as(x)) || is_not_nan(x);
      if ( eve::any(notdone) )
      {
        notdone =  next_interval(zetp, notdone, is_gez(x), r, x);
        if  ( eve::any(notdone) )
        {
          auto reflec = [zetp](auto x)
            {
              auto vp1 =  oneminus(x); //1-x
             return 2*pow_abs(2*pi(as(x)), -vp1)*cospi(T(0.5)*vp1)*tgamma(vp1)*zetp(vp1);
            };
          last_interval(reflec, notdone, r, x);
        }
      }
      return r;
    }
    else
      return apply_over(zeta, x);
  }
}
