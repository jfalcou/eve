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
#include <eve/module/dd/regular/traits.hpp>
#include <eve/module/dd/detail/utilities.hpp>


namespace eve::detail
{

  //================================================================================================
  //  unary functions
  //================================================================================================
//   template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::exp_, Z const& z) noexcept
//   {
//     auto n = nearest(z);
//     auto x = (z - n);
//     auto u = (((((((((((x +
//                         156)*x + 12012)*x +
//                       600600)*x + 21621600)*x +
//                     588107520)*x + 12350257920)*x +
//                   201132771840)*x + 2514159648000)*x +
//                 23465490048000)*x + 154872234316800)*x +
//               647647525324800)*x + 1295295050649600;
//     auto v = (((((((((((x -
//                         156)*x + 12012)*x -
//                       600600)*x + 21621600)*x -
//                     588107520)*x + 12350257920)*x -
//                   201132771840)*x + 2514159648000)*x -
//                 23465490048000)*x + 154872234316800)*x -
//               647647525324800)*x + 1295295050649600;
//     return pow(euler(as(z)), int(high(n)))*u/v;
//   }


//  template<typename Z>
//   EVE_FORCEINLINE auto
//   dd_unary_dispatch(eve::tag::exp_, Z const& x) noexcept
//   {
//      using dd_t =  element_type_t<Z>;
//     auto invlog2e = dd_t(0x1.71547652b82fep+0, 0x1.777d0ffda0d24p-56);
//   std::cout << invlog2e << std::endl;
// //     /* Pade' coefficients for exp(x) - 1
// //        Theoretical peak relative error = 2.2e-37,
// //        relative peak error spread = 9.2e-38
// //     */
// //     static long double P[5] = {
// //       3.279723985560247033712687707263393506266E-10L,
// //       6.141506007208645008909088812338454698548E-7L,
// //       2.708775201978218837374512615596512792224E-4L,
// //       3.508710990737834361215404761139478627390E-2L,
// //       9.999999999999999999999999999999999998502E-1L
// //     };
// //     static long double Q[6] = {
// //       2.980756652081995192255342779918052538681E-12L,
// //       1.771372078166251484503904874657985291164E-8L,
// //       1.504792651814944826817779302637284053660E-5L,
// //       3.611828913847589925056132680618007270344E-3L,
// //       2.368408864814233538909747618894558968880E-1L,
// //       2.000000000000000000000000000000000000150E0
// //     };
// //     /* C1 + C2 = -ln 2 */
// //     static long double C1 = -6.93145751953125E-1L;
// //     static long double C2 = -1.428606820309417232121458176568075500134E-6L;

// /* Express e**x = e**g 2**n
//  *   = e**g e**( n loge(2) )
//  *   = e**( g + n loge(2) )
//  */

//   auto px = nearest( invlog2e * x );
//   return px;
// // n = px;
// // x += px * C1;
// // x += px * C2;
// // /* rational approximation for exponential
// //  * of the fractional part:
// //  * e**x =  1 + 2x P(x**2)/( Q(x**2) - P(x**2) )
// //  */
// // xx = x * x;
// // px = x * polevll( xx, P, 4 );
// // xx = polevll( xx, Q, 5 );
// // x =  px/( xx - px );
// // x = 1.0L + x + x;

// // x = ldexpl( x, n );
// // return(x);

// // //     kumi::tuple < T, T, T > one_o_lg2 = {0x1.71547652b82fep+0, 0x1, 0x1.777d0ffda0d2p-56.d3e88eb578p-107};
// // //     auto alg = td_mul(a, alge)
// // //     return td_exp2(alg);
// //   }
// // //   //================================================================================================
// // //   //  Binary functions
// // //   //================================================================================================

// // //   EVE_FORCEINLINE auto
// // //   dd_binary_dispatch(eve::tag::pow_, auto const& z1, auto const& z2) noexcept
// // //   {
// // //     return z1 + z2;
// // //   }


  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::exp_, Z const& xx) noexcept
  {
     using dd_t =  element_type_t<Z>;
    auto invlog2e = dd_t(0x1.71547652b82fep+0, 0x1.777d0ffda0d24p-56);

    using A4 = kumi::result::generate_t<4, dd_t>;
    using A5 = kumi::result::generate_t<5, dd_t>;
    using A6 = kumi::result::generate_t<6, dd_t>;

    auto PQ = [](){
      if constexpr(std::same_as<underlying_type_t<dd_t>, double>)
      {
        const A5 P = {
          dd_t(0x1.689c05f36756p-32, -0x1.b875acd77e9acp-87),
          dd_t(0x1.49b837411c989p-21, 0x1.7ff39469597dcp-75),
          dd_t(0x1.1c09217291f46p-12, 0x1.a0d882ba61ba6p-67),
          dd_t(0x1.1f6f00b206f18p-5, -0x1.aefd0d051746ap-61),
          dd_t(0x1p+0, 0x0p+0)
        };
        const A6 Q = {
          dd_t(0x1.a381138db0fdfp-39, 0x1.b2be4132e41e3p-93),
          dd_t(0x1.3051c493f1ea3p-26, 0x1.8690d34e41bb5p-80),
          dd_t(0x1.f8ecb45c7ac45p-17, -0x1.c78d8611c4614p-71),
          dd_t(0x1.d968de20a03fbp-9, -0x1.f0e8a8b1c88b3p-63),
          dd_t(0x1.e50cd5ae58ce1p-3, 0x1.1f75b3b4b26c8p-57),
          dd_t(0x1p+1, 0x0p+0)
        };
        auto c2 =       dd_t(-0x1.7f7d1cf79abcap-20, 0x1.c4c67fc0d0951p-76);
        auto c1 =       dd_t(-0x1.62e4p-1, 0.0);
        return kumi::tuple{P, Q, c1, c2};
      }
      else
      {
        const A4 P = {
//          dd_t(0x1.689c06p-32, -0x1.93154p-61),
          dd_t(0x1.49b838p-21, -0x1.7dc6cep-46),
          dd_t(0x1.1c0922p-12, -0x1.1adc18p-37),
          dd_t(0x1.1f6fp-5, 0x1.640de4p-30),
          dd_t(0x1p+0, 0x0p+0)
        };
        const A5 Q = {
//          dd_t(0x1.a38114p-39, -0x1.c93c08p-65),
          dd_t(0x1.3051c4p-26, 0x1.27e3d4p-51),
          dd_t(0x1.f8ecb4p-17, 0x1.71eb12p-43),
          dd_t(0x1.d968dep-9, 0x1.0501fep-36),
          dd_t(0x1.e50cd6p-3, -0x1.469cc8p-29),
          dd_t(0x1p+1, 0x0p+0)
        };
        dd_t c1(-0.69314718055994530941723212145817656807550013436025);
        dd_t c2(c1+ 0.6931471805599453094172321214581765680755001343602);
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

    x = ldexp( x, high(nx) );
    x = if_else(xx == minf(as(xx)), zero(as(xx)), x);
    x = if_else(xx ==  inf(as(xx)), xx, x);
    return x;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::log_, Z const& x) noexcept
  {
    Z z(log(high(x)));
    z =   if_else(is_infinite(z), z, z+dec(x*exp(-z)));
    return if_else(is_ltz(x), nan(as(x)), z);
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::exp2_, Z const& xx) noexcept
  {
     using dd_t =  element_type_t<Z>;

    using A6 = kumi::result::generate_t<6, dd_t>;
    using A5 = kumi::result::generate_t<5, dd_t>;

    auto PQ = [](){
      if constexpr(std::same_as<underlying_type_t<dd_t>, double>)
      {
        const A5 P = {
          dd_t(0x1.3d6f2f5565773p+7, 0x1.19420194268e2p-54),
          dd_t(0x1.2e00e88b4606ap+19, -0x1.4fbc06f0a3626p-39),
          dd_t(0x1.0eb996d98ba45p+29, -0x1.ee9879c9c2b82p-26),
          dd_t(0x1.1d19e728a6be5p+37, -0x1.4c993b318897ep-17),
          dd_t(0x1.0840400c1c84bp+43, -0x1.bf94669b77458p-13)
        };

        const A6 Q = {
          dd_t(0x1p+0, 0x0p+0),
          dd_t(0x1.827029417a6adp+13, -0x1.6e6c49b8c7bcfp-44),
          dd_t(0x1.4d9860120d5dbp+24, 0x1.07b0fcd1e3bc6p-31),
          dd_t(0x1.457bc8296e4eap+33, -0x1.93cb82f41bec6p-24),
          dd_t(0x1.5b0c5bcbd7a73p+40, -0x1.18439cc87acd1p-15),
          dd_t(0x1.7d3bcb89794e5p+44, -0x1.b566fa30636ddp-12)
        };
        return kumi::tuple{P, Q};
      }
      else
      {
        const A5 P = {
          dd_t(0x1.3d6f3p+7, -0x1.553512p-18),
          dd_t(0x1.2e00e8p+19, 0x1.168c0ep-6),
          dd_t(0x1.0eb996p+29, 0x1.b31748p+4),
          dd_t(0x1.1d19e8p+37, -0x1.aeb284p+12),
          dd_t(0x1.08404p+43, 0x1.839096p+14)
        };
        const A6 Q = {
          dd_t(0x1p+0, 0x0p+0),
          dd_t(0x1.82702ap+13, -0x1.7d0b2ap-12),
          dd_t(0x1.4d986p+24, 0x1.20d5dcp-4),
          dd_t(0x1.457bc8p+33, 0x1.4b7274p+6),
          dd_t(0x1.5b0c5cp+40, -0x1.a142c6p+13),
          dd_t(0x1.7d3bccp+44, -0x1.da1ac6p+18),
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
    x = ldexp( x, high(nx) );
    x = if_else(xx == minf(as(xx)), zero(as(xx)), x);
    x = if_else(xx ==  inf(as(xx)), xx, x);
    return x;
  }

  template<typename Z>
  EVE_FORCEINLINE auto
  dd_unary_dispatch(eve::tag::log2_, Z const& x) noexcept
  {
    Z z(log2(high(x)));
    z =   if_else(is_infinite(z), z, z+invlog_2(as(x))*dec(x*exp2(-z)));
    return if_else(is_ltz(x), nan(as(x)), z);
  }


}
