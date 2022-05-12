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
  std::vector<elt_t> c0{1, 2, 3, 4, 0, 0, 0};
  std::vector<elt_t> c1{8, 9, 10};
  std::vector<elt_t> c2{1, 2, 3, 4, 5, 6, 7, 8, 0, 0};
  polynom_t p0(c0);
  polynom_t p1(c1);
  polynom_t p2(c2);
  TTS_EQUAL(valuation(p0), 3);
  TTS_EQUAL(valuation(p1), 0);
  TTS_EQUAL(valuation(p2), 2);
  TTS_EQUAL(valuation(polynom_t()), -1);
};
