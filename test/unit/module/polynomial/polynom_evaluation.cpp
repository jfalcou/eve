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
        , eve::test::generate(eve::test::randoms(0.0, 10.0))
        )
<typename T>(T const& x)
{
  using elt_t = eve::element_type_t<T>;
  using polynom_t = eve::polynom<elt_t>;
  std::vector<elt_t> const c0(10, 2.0);
  std::vector<elt_t> c1(c0);
  polynom_t p0(c0);
  TTS_EQUAL(p0(x), eve::horner(x, c0));
  TTS_EQUAL(p0(elt_t(2.0)), 2046.0f);
};
