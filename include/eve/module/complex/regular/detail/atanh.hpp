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
#include <boost/math/complex/atanh.hpp>
namespace eve
{

  namespace detail
  {
    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::atanh_, Z const& a0) noexcept
    {
      // This implementation is a simd (i.e. no branch) transcription and adaptation of the
      // boost_math code which itself is a transcription of the pseudo-code in:
      //
      // Eric W. Weisstein. "Inverse Hyperbolic Tangent."
      // From MathWorld--A Wolfram Web Resource.
      // http://mathworld.wolfram.com/InverseHyperbolicTangent.html
      //
      // Also: The Wolfram Functions Site,
      // http://functions.wolfram.com/ElementaryFunctions/ArcTanh/
      //
      // Also "Abramowitz and Stegun. Handbook of Mathematical Functions."
      // at : http://jove.prohosting.com/~skripty/toc.htm
      //
      auto [a0r, a0i] = a0;
      auto realinf = is_eqz(a0i) && is_infinite(a0r);
      using rtype = decltype(a0r);
      const rtype alpha_crossover(0.3);
      auto  ltzra0 = is_ltz(a0r);
      auto  ltzia0 = is_ltz(a0i);
      auto s_min = eve::sqrtsmallestposval(as(a0r))*2;
      auto s_max = eve::sqrtvalmax(as(a0r))/2;
      rtype const two = rtype(2);
      rtype inf =  eve::inf(as(a0r));
      rtype x = eve::abs(a0r);
      rtype y = eve::abs(a0i);
      rtype r = zero(as(a0r));
      rtype i = zero(as(a0r));
      auto gtxmax = (x > s_max);
      auto ltxmin = (x < s_min);
      auto gtymax = (y > s_max);
      auto ltymin = (y < s_min);
      rtype xx = eve::sqr(x);
      rtype yy = eve::sqr(y);
      rtype sqrabs = xx + yy;

      auto not_in_safe_zone = ((gtxmax || ltxmin) || (gtymax || ltymin));
      if(eve::any(not_in_safe_zone))
      {
        //treat underflow or overflow
        // one or both of x and y are small, calculate divisor carefully:
        rtype div = one(as(a0r));
        div += eve::if_else(ltxmin, xx, zero);
        div += eve::if_else(ltxmin, yy, zero);

        rtype alpha = x/div;
        alpha += alpha;

        auto test =  gtymax;
        // big y, medium x, divide through by y:
        rtype tmp_alpha = (two*x/y) / (y + xx/y);
        // small x and y, whatever alpha is, it's too small to calculate:
        tmp_alpha = eve::if_else(x > one(as(a0r)), tmp_alpha, zero);
        alpha = eve::if_else(test && (x > one(as(a0r))), tmp_alpha, alpha);

        test =  eve::logical_andnot(gtxmax, test);

        // big x small y, as above but neglect y^2/x:
        tmp_alpha =  two/x;
        // big x: divide through by x:
        tmp_alpha =  eve::if_else((y > one(as(a0r))),  two / (x + y*y/x), tmp_alpha);
        // big x and y: divide alpha through by x*y:
        tmp_alpha =  eve::if_else(gtymax, (two/y) / (x/y + y/x), tmp_alpha);
        // x or y are infinite: the result is 0
        tmp_alpha = eve::if_else((y == inf) || (x == inf), zero, tmp_alpha);

        alpha = eve::if_else(test, tmp_alpha, alpha);
        r = eve::if_else((alpha < alpha_crossover),
                        eve::log1p(alpha) - eve::log1p(-alpha),
                         eve::log(inc(two*x + xx)) - eve::log(sqr(dec(x)))
                       );
        test = (x == one(as(a0r))) && ltymin;
        r = eve::if_else(test, -(two*(eve::log(y) - eve::log_2(as(a0r)))), r);
        r *= rtype(0.25);
        //compute the imag part
        // y^2 is negligible:
        i =  eve::atan2(two*y, eve::oneminus(xx));
        i =  if_else(gtymax || gtxmax, pi(as(a0r)), i);
        rtype tmp_i = eve::if_else(ltymin, atan2(two*y, one(as(a0r))),
                                  eve::atan2(two*y, eve::oneminus(yy)));
        i =  if_else(ltxmin, tmp_i, i);
      }
      auto test0 = (inf == x) && (inf == y);
      if(eve::any(test0))
      {
        //inf x, inf y
        r = eve::if_else(test0, zero, r);
        i = eve::if_else(test0, pi(as(a0r)), r);
      }
      auto test = eve::is_nan(a0);

      if(eve::any(test))
      {
        //nan x, inf y
        r = eve::if_else(eve::is_nan(x) && (y == inf), zero, r);
        i = eve::if_else(eve::is_nan(x) && (y == inf), pi(as(a0r)), r);

        r = eve::if_else(is_nan(y) && (x == inf), zero, r);
        i = eve::if_else(is_nan(y) && (x == inf), y, i);

        r = eve::if_else(is_nan(y) && eve::is_eqz(x), zero, r);
        i = eve::if_else(is_nan(y) && is_eqz(x), allbits, i);
      }
      //compute for safe zone
      // the real part is given by:
      //
      // eve::real(atanh(z)) == log((1 + x^2 + y^2 + 2x) / (1 + x^2 + y^2 - 2x))
      //
      // however, when x is either large (x > 1/e) or very small
      // (x < e) then this effectively simplifies
      // to log(1), leading to wildly inaccurate results.
      // by dividing the above (top and bottom) by (1 + x^2 + y^2) we get:
      //
      // eve::real(atanh(z)) == log((1 + (2x / (1 + x^2 + y^2))) / (1 - (-2x / (1 + x^2 + y^2))))
      //
      // which is much more sensitive to the value of x, when x is not near 1
      // (remember we can compute log(1+x) for small x very accurately).
      //
      // the cross-over from one method to the other has to be determined
      // experimentally, the value used below appears correct to within a
      // factor of 2 (and there are larger errors from other parts
      // of the input domain anyway).
      //
      rtype alpha = x*two / (eve::inc(sqrabs));
      rtype sqrxm1 = eve::sqr(eve::dec(x));
      rtype tmp_r = eve::if_else((alpha < alpha_crossover),
                                eve::log1p(alpha) - log1p(-alpha),
                                eve::log1p(x+x + sqrabs) - eve::log(sqrxm1 + yy)
                                )*rtype(0.25);
      r = eve::if_else(not_in_safe_zone, r, tmp_r);

      // compute the imag part
      i = eve::if_else(not_in_safe_zone,
                      i,
                      eve::atan2(y+y, (oneminus(sqrabs)))
                     )*half(as(a0r));

      r = eve::if_else( ltzra0,-r, r);
      i = eve::if_else(is_infinite(y), pio_2(as(a0r))*sign(y), i);
      i = eve::if_else( ltzia0,-i, i);
      r = if_else(realinf, zero(as(a0r)), r);
      i = if_else(realinf, -sign(a0r)*pio_2(as(a0r)), i);
      return  Z{r, i};
    }
  }
}
