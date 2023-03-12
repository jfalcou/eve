//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
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

}
