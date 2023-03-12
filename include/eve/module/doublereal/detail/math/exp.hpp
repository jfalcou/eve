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

}
