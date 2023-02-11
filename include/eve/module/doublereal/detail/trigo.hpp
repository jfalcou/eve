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

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sin_, half_circle_type const & , Z const& a) noexcept
  //  requires(is_one_of<D>(types<full_circle_type, half_circle_type> {}))
  {
    Z x(half_circle(sin)(high(a)));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    x -= (asin(x)-a)*sqrt(oneminus(sqr(high(x))));
    return x;
  }

  namespace internal
  {
    template <typename Z > auto SC()
    {
      using doublereal_t =  element_type_t<Z>;
      using A6  = kumi::result::generate_t< 6, doublereal_t>;
      using A11 = kumi::result::generate_t<11, doublereal_t>;
      using A12 = kumi::result::generate_t<12, doublereal_t>;
      if constexpr(std::same_as<underlying_type_t<doublereal_t>, double>)
      {
        const A12 S = {
          doublereal_t(0x1.3d6c15b6d187p-84, 0x1.d093033090377p-138),
          doublereal_t(-0x1.7619a65f0be71p-75, 0x1.6f13e334d9fc6p-132),
          doublereal_t(0x1.71b8ee9a64e1dp-66, -0x1.21b81c560fb3ap-120),
          doublereal_t(-0x1.2f49b467cdf71p-57, 0x1.2f7c551051899p-111),
          doublereal_t(0x1.952c77030ab55p-49, -0x1.063cc46feac44p-103),
          doublereal_t(-0x1.ae7f3e733b81ep-41, -0x1.e0a1d2ce32f4ap-95),
          doublereal_t(0x1.6124613a86d09p-33, 0x1.f20d89d9a3f96p-87),
          doublereal_t(-0x1.ae64567f544e4p-26, 0x1.c063044344dadp-80),
          doublereal_t(0x1.71de3a556c734p-19, -0x1.c154f8e42416bp-73),
          doublereal_t(-0x1.a01a01a01a01ap-13, -0x1.a01a019fc52ccp-73),
          doublereal_t(0x1.1111111111111p-7, 0x1.1111111111108p-63),
          doublereal_t(-0x1.5555555555555p-3, -0x1.5555555555555p-57)
        };
        const A11 C = {
          doublereal_t(0x1.efc8801eb0a18p-80, 0x1.a4669bf7c5693p-134),
          doublereal_t(-0x1.0ce245980e119p-70, -0x1.1b3d9940e4a88p-129),
          doublereal_t(0x1.e542b8eb4f0ddp-62, -0x1.5dfa5f78a58cdp-119),
          doublereal_t(-0x1.6827863b2960bp-53, 0x1.f635a3ce31528p-107),
          doublereal_t(0x1.ae7f3e733b52p-45, -0x1.bfa449228b813p-99),
          doublereal_t(-0x1.93974a8c07c9cp-37, -0x1.f4310c460e0f9p-92),
          doublereal_t(0x1.1eed8eff8d898p-29, -0x1.2ba00315029f2p-83),
          doublereal_t(-0x1.27e4fb7789f5cp-22, -0x1.cbbbd75114fd1p-76),
          doublereal_t(0x1.a01a01a01a01ap-16, 0x1.a019fdf56450dp-76),
          doublereal_t(-0x1.6c16c16c16c17p-10, 0x1.f49f49f4a449p-65),
          doublereal_t(0x1.5555555555555p-5, 0x1.555555555555p-59),
        };

        auto dp1 =  doublereal_t(0x1.921fb54442d18p-1, 0x1p-55);
        auto dp2 =   doublereal_t(0x1.a62633145c06ep-59, 0x0p+0);
        auto dp3 =   doublereal_t(0x1.cd129024e088ap-116, 0x1.9f31d0082efaap-170);
        auto lossth(doublereal_t(3.6028797018963968E16)); /* 2^55 */
        return kumi::tuple{S, C, dp1, dp2, dp3, lossth};
      }
      else
      {
        const A6 S = {
          doublereal_t(0x1.5d8fd2p-33,  -0x1.731998p-64),
          doublereal_t(-0x1.ae5e5ap-26, -0x1.2523ecp-51),
          doublereal_t(0x1.71de36p-19,  -0x1.3056ecp-44),
          doublereal_t(-0x1.a01a02p-13,  0x1.90084p-39),
          doublereal_t(0x1.111112p-7,   -0x1.dde106p-32),
          doublereal_t(-0x1.555556p-3,   0x1.555558p-28),
        };
        const A6 C = {
          doublereal_t(-0x1.8fa49ap-37, -0x1.0c3536p-66),
          doublereal_t(0x1.1ee9d8p-29, -0x1.2c703ep-55),
          doublereal_t(-0x1.27e4f8p-22, 0x1.53b43ap-50),
          doublereal_t(0x1.a01a02p-16, -0x1.8deec2p-42),
          doublereal_t(-0x1.6c16c2p-10, 0x1.27d60ep-35),
          doublereal_t(0x1.555556p-5, -0x1.555556p-30),

        };

        auto dp1 =      doublereal_t(0x1.921fb4p-1, 0x0p+0);
        auto dp2 =      doublereal_t(0x1.4442dp-25, 0x0p+0);
        auto dp3 =      doublereal_t(0x1.84698ap-49, -0x1.cceba4p-75);
        auto lossth(doublereal_t(1.073741824e9)); /* 2^30*/
        return kumi::tuple{S, C, dp1, dp2, dp3, lossth};
      }
    }
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
