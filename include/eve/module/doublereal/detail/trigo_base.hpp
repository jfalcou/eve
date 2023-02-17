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
#include <eve/module/doublereal/doublereal.hpp>
namespace eve::detail
{
  namespace internal //just for doublereal
  {
    template < typename T >
    auto rem_piby2( T const& x )
    {
      if constexpr(scalar_value<T>) //T is doublereal<double>
      {
        if constexpr(std::same_as<underlying_type_t<T>, double>)
        {
          static double const zero = 0.0;
          static int const two_over_pi[] = {
            0xA2F983, 0x6E4E44, 0x1529FC, 0x2757D1, 0xF534DD, 0xC0DB62,
            0x95993C, 0x439041, 0xFE5163, 0xABDEBB, 0xC561B7, 0x246E3A,
            0x424DD2, 0xE00649, 0x2EEA09, 0xD1921C, 0xFE1DEB, 0x1CB129,
            0xA73EE8, 0x8235F5, 0x2EBB44, 0x84E99C, 0x7026B4, 0x5F7E41,
            0x3991D6, 0x398353, 0x39F49C, 0x845F8B, 0xBDF928, 0x3B1FF8,
            0x97FFDE, 0x05980F, 0xEF2F11, 0x8B5A0A, 0x6D1F6D, 0x367ECF,
            0x27CB09, 0xB74F46, 0x3F669E, 0x5FEA2D, 0x7527BA, 0xC7EBE5,
            0xF17B3D, 0x0739F7, 0x8A5292, 0xEA6BFB, 0x5FB11F, 0x8D5D08,
            0x560330, 0x46FC7B, 0x6BABF0, 0xCFBC20, 0x9AF436, 0x1DA9E3,
            0x91615E, 0xE61B08, 0x659985, 0x5F14A0, 0x68408D, 0xFFD880,
            0x4D7327, 0x310606, 0x1556CA, 0x73A8C9, 0x60E27B, 0xC08C6B,
          };

          double tx[6];
          int e0,i,nx,n;
          auto z = eve::abs( x );
          if ( z <= eve::pio_4(eve::as(z)) )            /* |x| ~<= pi/4 , no need for reduction */
          {
            return kumi::tuple{T(0), x, T(0)};
          }

          auto toInt = [](auto t){
            auto x = eve::trunc(t);
            return static_cast< long long >(eve::high(x)) + static_cast< long long >(eve::low(x));
          };

          /* set z = scalbn( |x|, -ilogb( x ) + 23 ) */
          e0  = eve::exponent( x ) - 23;
          z = eve::ldexp( z, -e0 );
          for ( i = 0; i < 5; i++ )
          {
            tx[i] = toInt(z);
            z     = eve::ldexp( z - tx[ i ], 24 );
          }
          tx[5] = toInt(z);
          double remainder[3];
          nx = 6;
          while ( tx[ nx - 1] == zero ) nx--; /* skip zero terms */
          n  =  eve::detail::__kernel_rem_pio2( tx, remainder, e0, nx, 3, two_over_pi );

          if ( eve::is_ltz(x) )
          {
            remainder[0] = -remainder[0];
            remainder[1] = -remainder[1];
            remainder[2] = -remainder[2];
            n = -n;
          }
          return kumi::tuple{T(double(n)), T(remainder[0], remainder[1]), T(remainder[2])};
        }
      }
      else if constexpr(simd_value<T>)
      {
        using   u_t =eve::underlying_type_t<T>;
        //       using elt_t = doublereal<eve::underlying_type_t<T>>;

        constexpr uint32_t size = cardinal_v<T>;
        constexpr auto     algt = alignment_v<T>;

        alignas(algt) std::array<u_t, size> tmph, tmpl;
        alignas(algt) std::array<u_t, size> txrh, txrl;
        alignas(algt) std::array<u_t, size> tyrh, tyrl;
        for( uint32_t i = 0; i != size; ++i )
        {
          auto [a, b, c] = rem_piby2(x.get(i));
          kumi::tie(tmph[i], tmpl[i]) = a;
          kumi::tie(txrh[i], txrl[i]) = b;
          kumi::tie(tyrh[i], tyrl[i]) = c;
        }
        auto tmp = T( eve::load(eve::as_aligned(&tmph[0]), cardinal_t<T> {}), eve::load(eve::as_aligned(&tmpl[0]), cardinal_t<T> {}));
        auto txr = T( eve::load(eve::as_aligned(&txrh[0]), cardinal_t<T> {}), eve::load(eve::as_aligned(&txrl[0]), cardinal_t<T> {}));
        auto tyr = T( eve::load(eve::as_aligned(&tyrh[0]), cardinal_t<T> {}), eve::load(eve::as_aligned(&tyrl[0]), cardinal_t<T> {}));
        return kumi::make_tuple(tmp, txr, tyr);
      }
    }

    template <typename Z > auto SC()
    {
      using doublereal_t =  element_type_t<Z>;
      using A6  = kumi::result::generate_t< 6, doublereal_t>;
      using A11 = kumi::result::generate_t<11, doublereal_t>;
      using A12 = kumi::result::generate_t<12, doublereal_t>;
      if constexpr(std::same_as<eve::underlying_type_t<doublereal_t>, double>)
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

//     template<typename Z> auto sin_eval(Z const& xx) noexcept
//     {
//       auto [S, C, dp1, dp2, dp3, lossth] = internal::SC<Z>();
//       auto sign = signnz(xx);
//       auto x = eve::abs(xx);
//       auto toobig = x >  lossth;

//       auto y = floor( x/pio_4(as(x)) ); /* integer part of x/PIO4 */

//       // strip high bits of integer part to prevent integer overflow */
//       auto z = ldexp( y, -4 );
//       z = floor(z);           /* integer part of y/8 */
//       z = y - ldexp( z, 4 );  /* y - 16 * (y/16) */

//       auto     yj = z;
//       auto test = is_odd(yj);
//       y =  if_else(test, y+1, y);
//       yj=  if_else(test, yj+1, yj);
//       yj =  yj-trunc(yj/8)*8;
//       test =  yj > Z(3);
//       sign = if_else(test, -sign, sign);
//       yj    = if_else(test, yj-4, yj);

//       // Extended precision modular arithmetic */
//       z = ((x - y * dp1) - y * dp2) - y * dp3;

//       auto zz = sqr(z);
//       auto r = if_else( Z(yj) == Z(1) || Z(yj) == Z(2),
//                         oneminus(ldexp(zz, -1))+zz*zz*horner(zz, C)
//                       , z  +  z * (zz * horner( zz, S)));
//       return if_else(toobig, nan(as(x)), sign*r);
//     }

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
