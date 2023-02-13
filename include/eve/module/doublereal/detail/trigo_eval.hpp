//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
namespace eve::detail
{
  namespace internal //just for doublereal
  {
    template<typename Z> auto sin_eval(Z const& xx) noexcept
    {
      auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
      auto sign = signnz(xx);
      auto x = eve::abs(xx);
      auto toobig = x >  lossth;

      auto y = floor( x/pio_4(as(x)) ); /* integer part of x/PIO4 */

      // strip high bits of integer part to prevent integer overflow */
      auto z = ldexp( y, -4 );
      z = floor(z);           /* integer part of y/8 */
      z = y - ldexp( z, 4 );  /* y - 16 * (y/16) */

      auto     yj = z;
      auto test = is_odd(yj);
      y =  if_else(test, y+1, y);
      yj=  if_else(test, yj+1, yj);
      yj =  yj-trunc(yj/8)*8;
      test =  yj > Z(3);
      sign = if_else(test, -sign, sign);
      yj    = if_else(test, yj-4, yj);

      // Extended precision modular arithmetic */
      z = ((x - y * dp1) - y * dp2) - y * dp3;

      auto zz = sqr(z);
      auto r = if_else( Z(yj) == Z(1) || Z(yj) == Z(2),
                        oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C)
                      , z  +  z * (zz * horner( zz, S)));
      return if_else(toobig, nan(as(x)), sign*r);
    }

//     template<typename Z> auto cos_eval(Z const& xx) noexcept
//     {
//       auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
//       auto sign = one(as((xx)));
//       auto x = eve::abs(xx);
//       auto toobig = x >  lossth;

//       auto y = floor( x/pio_4(as(x)) ); // integer part of x/PIO4

//       // strip high bits of integer part to prevent integer overflow
//       auto z = ldexp( y, -4 );
//       z = floor(z);           // integer part of y/8
//       z = y - ldexp( z, 4 );  // y - 16 * (y/16)

//       auto yj = z;
//       auto test = is_odd(yj);
//       y =  if_else(test, y+1, y);
//       yj =  if_else(test, yj+1, yj);
//       yj =  yj-trunc(yj/8)*8;
//       test =  yj > Z(3);
//       yj    = if_else(test, yj-4, yj);
//       sign = if_else(test != (yj > one(as(yj))), -sign, sign);

//       // Extended precision modular arithmetic
//       z = ((x - y * dp1) - y * dp2) - y * dp3;

//       auto zz = sqr(z);
//       auto r = if_else( Z(yj) == Z(1) || Z(yj) == Z(2)
//                       , z  +  z * (zz * horner( zz, S))
//                       , oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C));
//       return if_else(toobig, nan(as(x)), sign*r);
//     }

//     template<typename Z> auto sincos_eval( Z const& xx) noexcept
//     {
//       auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
//       auto csign = one(as((xx)));
//       auto ssign = signnz(xx);
//       auto x = eve::abs(xx);
//       auto toobig = x >  lossth;

//       auto y = floor( x/pio_4(as(x)) ); // integer part of x/PIO4

//       // strip high bits of integer part to prevent integer overflow
//       auto z = ldexp( y, -4 );
//       z = floor(z);           // integer part of y/8
//       z = y - ldexp( z, 4 );  // y - 16 * (y/16)

//       auto yj = z;
//       auto test = is_odd(yj);
//       y =  if_else(test, y+1, y);
//       yj =  if_else(test, yj+1, yj);
//       yj =  yj-trunc(yj/8)*8;
//       test =  yj > Z(3);
//       yj    = if_else(test, yj-4, yj);

//       csign = if_else(test != (yj > one(as(yj))), -csign, csign);
//       ssign = if_else(test, -ssign, ssign);

//       // Extended precision modular arithmetic
//       z = ((x - y * dp1) - y * dp2) - y * dp3;

//       auto zz = sqr(z);
//       auto r1 =  z  +  z * (zz * horner( zz, S));
//       auto r2 =  oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C);
//       test = Z(yj) == Z(1) || Z(yj) == Z(2);
//       auto sr = if_else( test, r2, r1);
//       auto cr = if_else( test, r1, r2);
//       sr = if_else(toobig, nan(as(x)), ssign*sr);
//       cr = if_else(toobig, nan(as(x)), csign*cr);
//       return kumi::tuple{sr, cr};
//     }

  }
}
