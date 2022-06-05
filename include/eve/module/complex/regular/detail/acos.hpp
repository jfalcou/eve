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
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::acos_, Z const& a0) noexcept
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
      auto  gtzia0 = is_gtz(a0i);
      //
      // Begin by insuring a0r >= 0 and imag(a0) >= 0 :
      //
      rtype x = eve::abs(a0r);
      rtype y = eve::abs(a0i);
      rtype proper_real = eve::acos(x);
      auto lexone = (x <= one(as(x)));
      auto is_proper_real = logical_and(is_real(a0), lexone);

      auto s_min = eve::sqrtsmallestposval(as(x))*4;
      auto s_max = eve::sqrtvalmax(as(x))/8;
      rtype xp1 = eve::inc(x);
      rtype xm1 = eve::dec(x);
      auto not_in_safe_zone = (((x > s_max) || (x < s_min)) || ((y > s_max) || (y < s_min)));
      //compute for safe zone
      rtype r, i;
      rtype yy = eve::sqr(y);
      rtype tr = eve::sqrt(sqr(xp1) + yy); //hypot for pedantic ?
      rtype ts = eve::sqrt(sqr(xm1) + yy); //hypot for pedantic ?
      rtype a = eve::average(tr, ts);
      rtype b = x/a;
      //compute r for b >  b_crossover
      rtype apx = a + x;
      r = if_else(lexone,
                  eve::atan(eve::sqrt(half(as(x))*apx*(yy/(tr+xp1)+(ts-xm1)))/x),
                  eve::atan((y*eve::sqrt(half(as(x))*(apx/(tr+xp1)+apx/(ts+xm1))))/x)
        );
      // r is computed
      r = if_else((b <= b_crossover), eve::acos(b), r);
      //compute am1 temporary for i for a <= a_crossover
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
        auto zone1 =  (y <= eve::eps(as(x))*eve::abs(xm1));
        if (eve::any(logical_and(zone1, not_in_safe_zone)))
        {
          rtype rr = if_else(lexone, proper_real, zero);
          rtype ii = if_else(lexone, y/eve::sqrt(-xp1*xm1),
                             if_else((valmax(as(x))/xp1 > xm1),
                                     eve::log1p(xm1 + eve::sqrt(xp1*xm1)),
                                     log_2(as(x)) + eve::log(x)
                               )
            );
          r = if_else(zone1, rr, r);
          i = if_else(zone1, ii, i);
        }
        auto zone2 = (y <= s_min);
        auto not_treated = logical_notand(zone1, not_in_safe_zone);
        if (eve::any(logical_and(zone2, not_treated)))
        {
          rtype sqrty =  eve::sqrt(y);
          r = if_else(zone2, sqrty, r);
          i = if_else(zone2, sqrty, i);
        }
        auto zone3 = (dec(eps(as(x))*y) >= x);
        not_treated = logical_notand(zone2, not_treated);
        if (eve::any(logical_and(zone3, not_treated)))
        {
          r = if_else(zone3,  pio_2(as(x)), r);
          i = if_else(zone3,  log_2(as(x)) + eve::log(y), i);
        }
        auto zone4 = (x > one(as(x)));
        not_treated = logical_notand(zone3, not_treated);
        if (eve::any(logical_and(zone4, not_treated)))
        {
          r = if_else(zone4, eve::atan(y/x), r);
          i = if_else(zone4, log_2(as(x)) + eve::log(y) + half(as(x))*eve::log1p(sqr(x/y)), i);
        }
        not_treated = logical_notand(zone4, not_treated);
        if (eve::any(not_treated))
        {
          rtype aa = eve::sqrt(eve::inc(sqr(y)));
          r = if_else(not_treated, pio_2(as(x)), r);
          i = if_else(not_treated, half(as(x))*eve::log1p(2*y*(y+aa)), i);
        }
      }
      if (eve::any(eve::is_not_finite(a0)))
      {
        auto nanx = eve::is_nan(x);
        auto nany = eve::is_nan(y);
        auto infx = (x == inf(as(x))) ;
        auto infy = (y == inf(as(x))) ;
        if (eve::any(infx))
        {
          r = eve::if_else(infx, zero, r);
          i = eve::if_else(infx, inf(as(x)), i);
          r = eve::if_else(logical_and(infx, infy), pio_4(as(x)), r);
          i = eve::if_else(logical_and(infx, infy), inf(as(x)), i);

          r =  if_else(logical_and(infx, nany), y, r);
          i =  if_else(logical_and(infx, nany), minf(as(x)), i);
        }
        if (eve::any(nanx))
        {
          r =  if_else(nanx, x, r);
          i =  if_else(nanx, x, i);
          i =  if_else(logical_and(nanx, infy), y, i);
        }
        auto test = logical_notand(logical_or(infx, nanx), infy);
        if (eve::any(test))
        {
          r = if_else(logical_and(infy, test), pio_2(as(x)), r);
          i = if_else(logical_and(infy, test), y, i);
        }
        test = logical_notand(logical_or(infx, nanx), nany);
        r = if_else(test,if_else(eve::is_imag(a0), pio_2(as(x)), y), r);
        i = if_else(test,y,i);
      }
      // use proper real results
      r = if_else(is_proper_real, proper_real,   r);
      i = if_else(is_proper_real, zero, i);
      // restore signs
      r = if_else(ltzra0, pi(as(x))-r, r);
      i = if_else(gtzia0, -i, i);
      return Z{r, i};
    }
  }
}
