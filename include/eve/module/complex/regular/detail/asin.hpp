//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/complex/regular/traits.hpp>

namespace eve
{

  namespace detail
  {
    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::asin_, Z const& a0) noexcept
    {
      // This implementation is a simd transcription and adaptation of the boost_math code
      // which itself is a transcription of the pseudo-code in:
      //
      // "Implementing the complex Arcsine and Arccosine Functions using Exception Handling."
      // T E Hull, Thomas F Fairgrieve and Ping Tak Peter Tang.
      // ACM Transactions on Mathematical Software, Vol 23, No 3, Sept 1997.
      //
      auto [a0r, a0i] = a0;
      using rtype = decltype(a0r);
      const rtype a_crossover(1.5);
      const rtype b_crossover(0.6417);
      auto  ltzra0 = is_ltz(a0r);
      auto  ltzia0 = is_ltz(a0i);

      //
      // Begin by insuring real(a0) >= 0 and imag(a0) >= 0 :
      //

      rtype x = eve::abs(a0r);
      rtype y = eve::abs(a0i);
      rtype proper_real = eve::asin(x);
      auto lexone = (x <= one(as(a0r)));
      auto is_proper_real = is_real(a0) && lexone;

      auto s_min = eve::sqrtsmallestposval(as(x))*4;
      auto s_max = eve::sqrtvalmax(as(x))/8;
      rtype xp1 =  eve::inc(x);
      rtype xm1 =  eve::dec(x);
      auto not_in_safe_zone = (((x > s_max) || (x < s_min)) || ((y > s_max) || (y < s_min)));
      //compute for safe zone
      rtype r, i;
      rtype yy = eve::sqr(y);
      rtype tr = eve::sqrt(eve::sqr(xp1) + yy);//hypot for pedantic ?
      rtype ts = eve::sqrt(eve::sqr(xm1) + yy);//hypot for pedantic ?
      rtype a = eve::average(tr, ts);
      rtype b = x/a;
      //compute r for b >  b_crossover
      rtype apx = a + x;
      r = if_else(lexone,
                  eve::atan(x/eve::sqrt(half(as(a0r))*apx*(yy/(tr+xp1)+(ts-xm1)))),
                  eve::atan(x/(y*eve::sqrt(half(as(a0r))*(apx/(tr+xp1)+apx/(ts+xm1)))))
                 );
      // r is computed
      r = if_else((b <= b_crossover), r, eve::asin(b));
      //compute am 1 temporary for i for a <= a_crossover
      rtype tmp = yy/(tr+xp1);
      rtype am1 = if_else(lexone,
                          eve::average(tmp, yy/(ts-xm1)),
                          eve::average(tmp, (ts+xm1)));
      i =  if_else((a <= a_crossover),
                   eve::log1p(am1 + eve::sqrt(am1*(eve::inc(a)))),
                   eve::log(a + eve::sqrt(eve::dec(eve::sqr(a))))
                  );
      // i is computed
      //compute for exception zone
      if (eve::any(not_in_safe_zone))
      {
        auto zone1 =  (y <= eve::eps(as(a0r))*eve::abs(xm1));
        if (eve::any(logical_and(zone1, not_in_safe_zone)))
        {
          rtype rr = if_else(lexone, eve::asin(x), pio_2(as(a0r)));
          rtype ii = if_else(lexone, y/eve::sqrt(xp1*xm1),
                             if_else((valmax(as(a0r))/xp1 > xm1),
                                     eve::log1p(xm1 + eve::sqrt(xp1*xm1)),
                                     log_2(as(a0r)) + eve::log(x)
                                    )
                            );
          r = if_else(zone1, rr, r);
          i = if_else(zone1, ii, i);
        }
        auto zone2 = (y <= s_min);
        auto not_treated = logical_notand(zone1, not_in_safe_zone);
        if (eve::any(logical_and(zone2, not_treated)))
        {
          r = if_else(zone2, pio_2(as(a0r)) - eve::sqrt(y), r);
          i = if_else(zone2, eve::sqrt(y), i);
        }
        auto zone3 = (eve::dec(eps(as(a0r))*y) >= x);
        not_treated = logical_notand(zone2, not_treated);
        if (eve::any(logical_and(zone3, not_treated)))
        {
          r = if_else(zone3,  x/y, r);
          i = if_else(zone3,  log_2(as(a0r)) + eve::log(y), i);
        }
        auto zone4 = (x > one(as(a0r)));
        not_treated = logical_notand(zone3, not_treated);
        if (eve::any(logical_and(zone4, not_treated)))
        {
          r = if_else(zone4, eve::atan(x/y), r);
          i = if_else(zone4, log_2(as(a0r)) + eve::log(y) + half(as(a0r))*eve::log1p(eve::sqr(x/y)), i);
        }
        not_treated = logical_notand(zone4, not_treated);
        if (eve::any(not_treated))
        {
          rtype aa = eve::sqrt(eve::inc(eve::sqr(y)));
          r = if_else(not_treated, x/aa, r);
          i = if_else(not_treated, half(as(a0r))*eve::log1p(2*y*(y+aa)), i);
        }
      }
      if (eve::any(is_not_finite(a0)))
      {
        auto nanx = is_nan(x);
        auto nany = is_nan(y);
        auto infx = (x == inf(as(a0r))) ;
        auto infy = (y == inf(as(a0r))) ;
        if (eve::any(nanx))
        {
          r =  if_else(nanx, x, r);
          r =  if_else(nanx && infy, x, r);
          i =  if_else(nanx, x, i);
          i =  if_else(nanx && infy, y, i);
        }
        if (eve::any(nany))
        {
          auto isimag = is_imag(a0);
          r =  if_else(isimag && nany, zero, r);
          r =  if_else(logical_and(nany, infx),y, r);
          i =  if_else(isimag && nany, allbits, i);
          i =  if_else(nany && infx, x, i);
        }
        auto test = logical_notand(logical_or(nanx, nany), infx);
        if (eve::any(test))
        {
          r = if_else(infx && test,
                      if_else(infy, eve::pio_4(as(a0r)), eve::pio_2(as(a0r))),
                      r);
        }
        test = logical_notand(is_nan(x) || is_nan(y),
                              logical_andnot(infy, infx));
        r = if_else(test,zero,r);
      }
      // use proper real results

      r = if_else(is_proper_real, proper_real,   r);
      i = if_else(is_proper_real, zero, i);
      // restore signs
      r = if_else(ltzra0, -r, r);
      i = if_else(ltzia0, -i, i);
      return Z{r, i};
    }
  }
}
