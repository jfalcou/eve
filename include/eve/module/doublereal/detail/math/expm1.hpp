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
}
