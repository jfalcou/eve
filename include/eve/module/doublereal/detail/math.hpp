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
#include <eve/module/polynomial.hpp>
#include <eve/module/doublereal/regular/traits.hpp>
#include <eve/module/doublereal/detail/utilities.hpp>


namespace eve::detail
{



//================================================================================================
//  Unary functions
//================================================================================================

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::cbrt_, Z const& a) noexcept
  {
    if constexpr(has_native_abi_v<Z>)
    {
      auto pos = is_gtz(a);
      auto [r, e] = frexp(abs(a ));
      auto ee = int_(e);
      auto test = is_nez(ee-3*(ee/3));
      while ( eve::any(test) )
      {
        ee = inc[test](ee);
        r = if_else(test, ldexp(r,-1), r);
        test = is_nez(ee-3*(ee/3));
      }
      Z x(rec(cbrt(high(r))));
      x += x * oneminus(r * sqr(x) * x) * third(as(x));
      x += x * oneminus(r * sqr(x) * x) * third(as(x));
      x = rec(x);
      x = if_else(pos, x, -x);
      auto xx = ldexp( x, ee / 3 );
      return  if_else ( is_not_finite( a ) || is_eqz( a ), a, xx);
    }
    else return apply_over(cbrt, a);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::exp_, Z const& xx) noexcept
  {
     using doublereal_t =  element_type_t<Z>;
    auto invlog2e = doublereal_t(0x1.71547652b82fep+0, 0x1.777d0ffda0d24p-56);

    using A4 = kumi::result::generate_t<4, doublereal_t>;
    using A5 = kumi::result::generate_t<5, doublereal_t>;
    using A6 = kumi::result::generate_t<6, doublereal_t>;

    auto PQ = [](){
      if constexpr(std::same_as<underlying_type_t<doublereal_t>, double>)
      {
        const A5 P = {
          doublereal_t(0x1.689c05f36756p-32, -0x1.b875acd77e9acp-87),
          doublereal_t(0x1.49b837411c989p-21, 0x1.7ff39469597dcp-75),
          doublereal_t(0x1.1c09217291f46p-12, 0x1.a0d882ba61ba6p-67),
          doublereal_t(0x1.1f6f00b206f18p-5, -0x1.aefd0d051746ap-61),
          doublereal_t(0x1p+0, 0x0p+0)
        };
        const A6 Q = {
          doublereal_t(0x1.a381138db0fdfp-39, 0x1.b2be4132e41e3p-93),
          doublereal_t(0x1.3051c493f1ea3p-26, 0x1.8690d34e41bb5p-80),
          doublereal_t(0x1.f8ecb45c7ac45p-17, -0x1.c78d8611c4614p-71),
          doublereal_t(0x1.d968de20a03fbp-9, -0x1.f0e8a8b1c88b3p-63),
          doublereal_t(0x1.e50cd5ae58ce1p-3, 0x1.1f75b3b4b26c8p-57),
          doublereal_t(0x1p+1, 0x0p+0)
        };
        auto c2 =       doublereal_t(-0x1.7f7d1cf79abcap-20, 0x1.c4c67fc0d0951p-76);
        auto c1 =       doublereal_t(-0x1.62e4p-1, 0.0);
        return kumi::tuple{P, Q, c1, c2};
      }
      else
      {
        const A4 P = {
//          doublereal_t(0x1.689c06p-32, -0x1.93154p-61),
          doublereal_t(0x1.49b838p-21, -0x1.7dc6cep-46),
          doublereal_t(0x1.1c0922p-12, -0x1.1adc18p-37),
          doublereal_t(0x1.1f6fp-5, 0x1.640de4p-30),
          doublereal_t(0x1p+0, 0x0p+0)
        };
        const A5 Q = {
//          doublereal_t(0x1.a38114p-39, -0x1.c93c08p-65),
          doublereal_t(0x1.3051c4p-26, 0x1.27e3d4p-51),
          doublereal_t(0x1.f8ecb4p-17, 0x1.71eb12p-43),
          doublereal_t(0x1.d968dep-9, 0x1.0501fep-36),
          doublereal_t(0x1.e50cd6p-3, -0x1.469cc8p-29),
          doublereal_t(0x1p+1, 0x0p+0)
        };
        doublereal_t c1(-0.69314718055994530941723212145817656807550013436025);
        doublereal_t c2(c1+ 0.6931471805599453094172321214581765680755001343602);
        return kumi::tuple{P, Q, c1, c2};
      }
    };


    auto [P, Q, c1, c2] = PQ();
    // Express e**x = e**g 2**n
    //   = e**g e**( n loge(2) )
    //   = e**( g + n loge(2) )
    //
    auto nx = nearest( invlog2e * xx );
    auto x = xx + nx * c1;
    x += nx * c2;
    // rational approximation for exponential
    // of the fractional part:
    // e**x =  1 + 2x P(x**2)/( Q(x**2) - P(x**2) )

    auto x2 = sqr(x);
    auto px = x * horner(x2, P);
    auto qx =  horner(x2, Q);
    x =  px/( qx - px );
    x = inc(x + x);

    x = pedantic(ldexp)( x, high(nx) );
    x = if_else(xx == minf(as(xx)), zero, x);
    x = if_else(xx ==  inf(as(xx)), xx, x);
    return x;
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::log_, Z const& x) noexcept
  {
    Z z(log(high(x)));
    z =   if_else(is_infinite(z), z, z+dec(x*exp(-z)));
    return if_else(is_ltz(x), nan(as(x)), z);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::exp2_, Z const& xx) noexcept
  {
     using doublereal_t =  element_type_t<Z>;

    using A6 = kumi::result::generate_t<6, doublereal_t>;
    using A5 = kumi::result::generate_t<5, doublereal_t>;

    auto PQ = [](){
      if constexpr(std::same_as<underlying_type_t<doublereal_t>, double>)
      {
        const A5 P = {
          doublereal_t(0x1.3d6f2f5565773p+7, 0x1.19420194268e2p-54),
          doublereal_t(0x1.2e00e88b4606ap+19, -0x1.4fbc06f0a3626p-39),
          doublereal_t(0x1.0eb996d98ba45p+29, -0x1.ee9879c9c2b82p-26),
          doublereal_t(0x1.1d19e728a6be5p+37, -0x1.4c993b318897ep-17),
          doublereal_t(0x1.0840400c1c84bp+43, -0x1.bf94669b77458p-13)
        };

        const A6 Q = {
          doublereal_t(0x1p+0, 0x0p+0),
          doublereal_t(0x1.827029417a6adp+13, -0x1.6e6c49b8c7bcfp-44),
          doublereal_t(0x1.4d9860120d5dbp+24, 0x1.07b0fcd1e3bc6p-31),
          doublereal_t(0x1.457bc8296e4eap+33, -0x1.93cb82f41bec6p-24),
          doublereal_t(0x1.5b0c5bcbd7a73p+40, -0x1.18439cc87acd1p-15),
          doublereal_t(0x1.7d3bcb89794e5p+44, -0x1.b566fa30636ddp-12)
        };
        return kumi::tuple{P, Q};
      }
      else
      {
        const A5 P = {
          doublereal_t(0x1.3d6f3p+7, -0x1.553512p-18),
          doublereal_t(0x1.2e00e8p+19, 0x1.168c0ep-6),
          doublereal_t(0x1.0eb996p+29, 0x1.b31748p+4),
          doublereal_t(0x1.1d19e8p+37, -0x1.aeb284p+12),
          doublereal_t(0x1.08404p+43, 0x1.839096p+14)
        };
        const A6 Q = {
          doublereal_t(0x1p+0, 0x0p+0),
          doublereal_t(0x1.82702ap+13, -0x1.7d0b2ap-12),
          doublereal_t(0x1.4d986p+24, 0x1.20d5dcp-4),
          doublereal_t(0x1.457bc8p+33, 0x1.4b7274p+6),
          doublereal_t(0x1.5b0c5cp+40, -0x1.a142c6p+13),
          doublereal_t(0x1.7d3bccp+44, -0x1.da1ac6p+18),
        };
        return kumi::tuple{P, Q};
      }
    };


    auto [P, Q] = PQ();
    auto nx = nearest(xx);
    auto x =  xx-nx;
    // rational approximation
    // exp2(x) = 1.0 +  2xP(xx)/(Q(xx) - P(xx))
    // where xx = x**2
    auto x2 = sqr(x);
    auto px = x * horner(x2, P);
    auto qx =  horner(x2, Q);
    x =  px/( qx - px );
    x = inc(x + x);
    x = pedantic(ldexp)( x, high(nx) );
    x = if_else(xx == minf(as(xx)), zero(as(xx)), x);
    x = if_else(xx ==  inf(as(xx)), xx, x);
    return x;
  }

/// TODO ne fonctionne pas
//   template<typename Z>
//   auto
//   doublereal_unary_dispatch(eve::tag::exp10_, Z const& xx) noexcept
//   {
//     using doublereal_t =  element_type_t<Z>;

//     using A6 = kumi::result::generate_t<6, doublereal_t>;
//     using A7 = kumi::result::generate_t<7, doublereal_t>;
//     using A3 = kumi::result::generate_t<3, doublereal_t>;
//     using A4 = kumi::result::generate_t<4, doublereal_t>;

//     auto PQ = [](){
//       if constexpr(std::same_as<underlying_type_t<doublereal_t>, double>)
//       {
//         const A6 P = {
//           doublereal_t(0x1.0f4753592b646p+6, 0x1.c16dc118e7a8ap-48),
//           doublereal_t(0x1.813bc6e0b2e8bp+15, 0x1.25e8b175ad4ccp-39),
//           doublereal_t(0x1.161b0d6ece1f9p+23, -0x1.a41adfbf85838p-32),
//           doublereal_t(0x1.186516dcd6e45p+29, -0x1.c05925f15183p-25),
//           doublereal_t(0x1.81af4f357c5a9p+33, 0x1.25455694106cbp-22),
//           doublereal_t(0x1.f5f69601851d9p+35, 0x1.3b27a0722befdp-21),
//         };

//         const A7 Q = {
//           doublereal_t(0x1p+0, 0x0p+0),
//           doublereal_t(0x1.1bb3480b1f4cap+11, -0x1.0c2ed19cf48afp-44),
//           doublereal_t(0x1.78946958ce2dcp+19, 0x1.c420da8bd115bp-36),
//           doublereal_t(0x1.3d1bf9db25735p+26, 0x1.4780e79bd0f14p-28),
//           doublereal_t(0x1.7c944f74983a9p+31, -0x1.e8c03ecf1625bp-23),
//           doublereal_t(0x1.1462ca3250891p+35, -0x1.628803c467fa1p-19),

//         };
//         doublereal_t log210 = doublereal_t(0x1.a934f0979a371p+1, 0x1.7f2495fb7fa6ep-53);
//         doublereal_t lg102a = doublereal_t(0x1.344p-2, 0x0p+0);
//         doublereal_t lg102b = doublereal_t(0x1.3509f79fef312p-18, -0x1.da994fd20dba2p-75);
//         return kumi::tuple{P, Q, log210, lg102a, lg102b};
//       }
//       else
//       {
//         const A3 P = {
//           doublereal_t(0x1.4fd76p-5, -0x1.9f3a46p-30),
//           doublereal_t(0x1.77d948p+3, -0x1.6754dap-22),
//           doublereal_t(0x1.96b7ap+8, 0x1.40d278p-18),
//         };
//         const A4 Q = {
//           doublereal_t(0x1p+0, 0x0p+0),
//           doublereal_t(0x1.545fdcp+6, 0x1.ca394p-19),
//           doublereal_t(0x1.3e05eep+10, 0x1.facefp-15),
//           doublereal_t(0x1.03f376p+11, 0x1.437db8p-15),

//         };
//         doublereal_t log210 = doublereal_t(0x1.a934fp+1, 0x1.2f346ep-24);
//         doublereal_t lg102a = doublereal_t(0x1.344p-2, 0x0p+0) ;
//         doublereal_t lg102b = doublereal_t(0x1.3509f8p-18, -0x1.80433cp-44);
//         return kumi::tuple{P, Q, log210, lg102a, lg102b};
//       }
//     };
//     auto [P, Q, log210, lg102a, lg102b] = PQ();
//  //     std::cout << "xx " << xx << std::endl;
// //      std::cout << "log210 *xx " << log210 *xx << std::endl;

//     auto nx = floor(log210 *xx+half(as(xx)));
// //     std::cout << "nx " << nx << std::endl;
//     auto x = xx - nx * lg102a;
//     x -= nx * lg102b;
// //    std::cout << "x " << x << std::endl;

//     auto x2 = sqr(x);
//     auto px = x * horner(x2, P);
//     auto qx =  horner(x2, Q);
//     x =  px/( qx - px );
//     x = inc(x + x);
//     x = pedantic(ldexp)( x, high(nx) );
//     x = if_else(xx == minf(as(xx)), zero(as(xx)), x);
//     x = if_else(xx == inf(as(xx)), xx, x);
//     return x;
//   }




  template<typename Z>
   auto
  doublereal_unary_dispatch(eve::tag::log2_, Z const& x) noexcept
  {
    Z z(log2(high(x)));
    z =   if_else(is_infinite(z), z, z+invlog_2(as(x))*dec(x*exp2(-z)));
    return if_else(is_ltz(x), nan(as(x)), z);
  }

    template<typename Z>
   auto
  doublereal_unary_dispatch(eve::tag::expm1_, Z const& xx) noexcept
  {
    using doublereal_t =  element_type_t<Z>;
    auto great = eve::abs(xx) >= half(as(xx));
    if (eve::all(great)) return dec(exp(xx));
    if constexpr(std::same_as<underlying_type_t<doublereal_t>, double>)
    {
      using A4 = kumi::result::generate_t<4, doublereal_t>;
      using A9 = kumi::result::generate_t<9, doublereal_t>;
      const A4 P = {
        doublereal_t(0x1.29f6b20961cp-22, 0x1.29f6b20961cp-82),
        doublereal_t(0x1.c01c01c01c01cp-13, 0x1.c01c01c01c01cp-73),
        doublereal_t(0x1.1111111111111p-5, 0x1.1111111111111p-61),
        doublereal_t(0x1p+0, 0x0p+0)
      };
      //{1/doublereal_t(3603600ll), 1/doublereal_t(4680ll),  1/doublereal_t(30ll), doublereal_t(1)};
      const A9 Q = {
        doublereal_t(0x1.08db48ebe51c7p-29, 0x1.d7aa2655dac39p-85),
        doublereal_t(-0x1.29f6b20961cp-23, -0x1.29f6b20961cp-83),
        doublereal_t(0x1.45e5d2ba42eap-18, 0x1.45e5d2ba42eap-78),
        doublereal_t(-0x1.c01c01c01c01cp-14, -0x1.c01c01c01c01cp-74),
        doublereal_t(0x1.a41a41a41a41ap-10, 0x1.069069069069p-64),
        doublereal_t(-0x1.1111111111111p-6, -0x1.1111111111111p-62),
        doublereal_t(0x1.ddddddddddddep-4, -0x1.1111111111111p-59),
        doublereal_t(-0x1p-1, 0x0p+0),
        doublereal_t(0x1p+0, 0x0p+0)
      };
      //     {1/doublereal_t(518918400ll), -1/doublereal_t(7207200ll), 1/doublereal_t(205920ll),
      //      -1/doublereal_t(9360ll), 1/doublereal_t(624ll), -1/doublereal_t(60ll), 7/doublereal_t(60ll),
      //      -1/doublereal_t(2.0), doublereal_t(1.0)};
      //////////////////////////////////////////////////////////////////////////////
      // Express e**x -1= e**g 2**n -1 = 2**n(e**g -1) + 2**n -1
      //       auto invlog2e = doublereal_t(0x1.71547652b82fep+0, 0x1.777d0ffda0d24p-56);
      //       auto nx = nearest( invlog2e * xx );
      //       auto x = xx + nx * c1;
      //       x += nx * c2;
      //       auto x2 = sqr(x);
      // TO DO AGAIN / PERHAPS CONSTRUCTOR PB SOMEWHERE
      //////////////////////////////////////////////////////////////////////////////
      auto x2 = sqr(xx);
      auto px = horner(x2, P);
      auto qx =   (horner)(xx, Q);
      auto x = xx*px/qx;
      x = if_else(xx == minf(as(xx)), mone(as(xx)), x);
      x = if_else(xx ==  inf(as(xx)), xx, x);
      //////////////////////////////////////////////////////////////////////////////
      //       auto factor = ldexp( one(as(x)), high(nx) );
      //       x = factor*(x*px/qx)+dec(factor);
      //       return x;
      // TO DO AGAIN / PERHAPS CONSTRUCTOR PB SOMEWHERE
      //////////////////////////////////////////////////////////////////////////////
       return if_else(great, dec(exp(xx)), x);

    }
    else
    {
      using A3 = kumi::result::generate_t<3, doublereal_t>;
      using A4 = kumi::result::generate_t<4, doublereal_t>;
      const A3 P = {
        doublereal_t(1.2617719307481059087798E-4),
        doublereal_t(3.0299440770744196129956E-2),
        doublereal_t(9.9999999999999999991025E-1)
      };
      const A4 Q = {
        doublereal_t(3.0019850513866445504159E-6),
        doublereal_t(2.5244834034968410419224E-3),
        doublereal_t(2.2726554820815502876593E-1),
        doublereal_t(2.0000000000000000000897E0)
      };
      auto x2 = sqr(xx);
      auto r = xx * horner( x2, P);
      r = 2*r/( horner( x2, Q) - r );
      if(eve::none(great)) return r;
      auto r1 = dec(exp(xx));
      return if_else(great, r1, r);
    }
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::log1p_, Z const& x) noexcept
  {
    Z z(log1p(high(x)));
    Z z1 = z-exp(-z)*(expm1(z)-x);
    z =   if_else(is_infinite(z), z, z1);
    return if_else(x < mone(as(x)), nan(as(x)), z);
  }

}
#include <eve/module/doublereal/detail/invtrig.hpp>
#include <eve/module/doublereal/detail/trigo.hpp>
