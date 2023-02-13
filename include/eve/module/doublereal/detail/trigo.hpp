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
#include <eve/module/doublereal/detail/trigo_base.hpp>

namespace eve::detail
{

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sin_, quarter_circle_type const &, Z const& a) noexcept
  //  requires(is_one_of<D>(types<full_circle_type, half_circle_type> {}))
  {
    Z x(quarter_circle(sin)(high(a)));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    return x;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sin_, half_circle_type const &, Z const& a) noexcept
  //  requires(is_one_of<D>(types<full_circle_type, half_circle_type> {}))
  {
    Z x(half_circle(sin)(high(a)));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    return x;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sin_, full_circle_type const & , Z const& a) noexcept
  {
    auto sign =  if_else(is_positive(a), one(as(a)), mone(as(a)));
    auto xx = eve::abs(a);
    auto [nn, x, dx] = internal::rem_piby2(xx);
    std::cout << "icitte " << x << std::endl;
    auto n = if_else(nn > 3, nn-4, nn);
    auto alpha = if_else(is_odd(n), zero, one(as(x)));
    auto beta  = if_else(is_odd(n), one(as(x)), zero);
    sign *=  if_else(n >= 2, mone(as(x)), one(as(x)));
    auto s =   sign*(sin)(x);
    auto c =   sign*(cos)(x);
    return s*alpha+c*beta;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sin_, medium_type const & , Z const& a) noexcept
  {
    auto sign =  if_else(is_positive(a), one(as(a)), mone(as(a)));
    auto xx = eve::abs(a);
    auto [nn, x, dx] = internal::rem_piby2(xx);
     std::cout << "a  " << a <<  std::endl;
     std::cout << "x  " << x <<  std::endl;
     std::cout << "nn  " << nn <<  std::endl;
     auto n = if_else(nn > 3, nn-4, nn);
//     std::cout << "x  " << x <<  std::endl;
//     std::cout << "dx " << dx<<  std::endl;
    auto alpha = if_else(is_odd(n), zero, one(as(x)));
    auto beta  = if_else(is_odd(n), one(as(x)), zero);
    sign *=  if_else(n >= 2, mone(as(x)), one(as(x)));
//     std::cout << "alpha " << alpha <<  std::endl;
//     std::cout << "beta  " << beta  <<  std::endl;
//     std::cout << "sign  " << sign  <<  std::endl;
    auto s =   sign*(sin)(x);
    auto c =   sign*(cos)(x);
    return s*alpha+c*beta;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::cos_, full_circle_type const & , Z const& a) noexcept
  {
    auto xx = eve::abs(a);
    auto [nn, x, dx] = internal::rem_piby2(xx);
    std::cout << "a  " << a <<  std::endl;
    std::cout << "x  " << x <<  std::endl;
    std::cout << "nn  " << nn <<  std::endl;
    auto n = if_else(nn > 3, nn-4, nn);
    auto alpha = if_else(is_odd(n), zero, one(as(x)));
    auto beta  = if_else(is_odd(n), mone(as(x)), zero);
    auto sign =  if_else(n >= 2, mone(as(x)), one(as(x)));
    auto s =   sign*(sin)(x);
    auto c =   sign*(cos)(x);
    return c*alpha+s*beta;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sin_, Z const& xx) noexcept
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

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::cos_, Z const& xx) noexcept
  {
    auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
    auto sign = one(as((xx)));
    auto x = eve::abs(xx);
    auto toobig = x >  lossth;

    auto y = floor( x/pio_4(as(x)) ); // integer part of x/PIO4

    // strip high bits of integer part to prevent integer overflow
    auto z = ldexp( y, -4 );
    z = floor(z);           // integer part of y/8
    z = y - ldexp( z, 4 );  // y - 16 * (y/16)

    auto yj = z;
    auto test = is_odd(yj);
    y =  if_else(test, y+1, y);
    yj =  if_else(test, yj+1, yj);
    yj =  yj-trunc(yj/8)*8;
    test =  yj > Z(3);
    yj    = if_else(test, yj-4, yj);
    sign = if_else(test != (yj > one(as(yj))), -sign, sign);

    // Extended precision modular arithmetic
    z = ((x - y * dp1) - y * dp2) - y * dp3;

    auto zz = sqr(z);
    auto r = if_else( Z(yj) == Z(1) || Z(yj) == Z(2)
                    , z  +  z * (zz * horner( zz, S))
                    , oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C));
    return if_else(toobig, nan(as(x)), sign*r);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sincos_, Z const& xx) noexcept
  {
    auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
    auto csign = one(as((xx)));
    auto ssign = signnz(xx);
    auto x = eve::abs(xx);
    auto toobig = x >  lossth;

    auto y = floor( x/pio_4(as(x)) ); // integer part of x/PIO4

    // strip high bits of integer part to prevent integer overflow
    auto z = ldexp( y, -4 );
    z = floor(z);           // integer part of y/8
    z = y - ldexp( z, 4 );  // y - 16 * (y/16)

    auto yj = z;
    auto test = is_odd(yj);
    y =  if_else(test, y+1, y);
    yj =  if_else(test, yj+1, yj);
    yj =  yj-trunc(yj/8)*8;
    test =  yj > Z(3);
    yj    = if_else(test, yj-4, yj);

    csign = if_else(test != (yj > one(as(yj))), -csign, csign);
    ssign = if_else(test, -ssign, ssign);

    // Extended precision modular arithmetic
    z = ((x - y * dp1) - y * dp2) - y * dp3;

    auto zz = sqr(z);
    auto r1 =  z  +  z * (zz * horner( zz, S));
    auto r2 =  oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C);
    test = Z(yj) == Z(1) || Z(yj) == Z(2);
    auto sr = if_else( test, r2, r1);
    auto cr = if_else( test, r1, r2);
    sr = if_else(toobig, nan(as(x)), ssign*sr);
    cr = if_else(toobig, nan(as(x)), csign*cr);
    return kumi::tuple{sr, cr};
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::tan_, Z const& xx) noexcept
  {
    auto [s, c] =  sincos(xx);
    return s/c;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::cot_, Z const& xx) noexcept
  {
    auto [s, c] =  sincos(xx);
    return c/s;
  }
}
