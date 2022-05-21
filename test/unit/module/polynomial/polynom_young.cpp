//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/polynomial.hpp>
#include <cmath>
#include <array>
#include <vector>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST( "Check behavior of horner on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0))
        )
<typename T>(T const&)
{
  using elt_t = eve::element_type_t<T>;
  using polynom_t = eve::polynom<elt_t>;
  using monom_t   = eve::monom<elt_t>;
  std::vector<elt_t> c0{1, 2, 3, 4, 5, 6, 7};
  std::vector<elt_t> c1{8, 9, 10};
  polynom_t p0(c0);
  polynom_t p1(c1);

  polynom_t y = young(2, p0);
  TTS_EQUAL(degree(y), 2);
  polynom_t yr = young_remainder(2, p0);
  TTS_EQUAL(degree(yr), degree(p0));
  TTS_GREATER_EQUAL(valuation(yr), degree(y)+1);
  TTS_EXPECT(p0 == (yr+y));
  polynom_t g = concat(y, yr/monom_t(elt_t(1), degree(y)+1));
  TTS_EXPECT(p0 == g);
  monom_t x5(elt_t(3), 5);
  TTS_EXPECT(young(3, x5) == monom_t());
  TTS_EXPECT(young(6, x5) == x5);
  TTS_EXPECT(young_remainder(6, x5) == monom_t());
  TTS_EXPECT(young_remainder(3, x5) == x5);
 };
