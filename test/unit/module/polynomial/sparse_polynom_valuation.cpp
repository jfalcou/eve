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
  using pair_t           = typename eve::sparse_polynom<elt_t>::pair_t;
  using sparse_polynom_t = eve::sparse_polynom<elt_t>;
  std::vector<pair_t> c0{{500, 1}, {2, -2}, {1, 4}, {0, -7}};
  std::vector<pair_t> c1{{5, -2}, {3, 4}};
  std::vector<pair_t> c2{{50, 1}, {5, -2}, {3, 4}};
  std::vector<pair_t> c3{{500, 1}};
  sparse_polynom_t p0(c0);
  sparse_polynom_t p1(c1);
  sparse_polynom_t p2(c2);
  sparse_polynom_t p3(c3);
  TTS_EQUAL(valuation(p0), 0);
  TTS_EQUAL(valuation(p1), 3);
  TTS_EQUAL(valuation(p2), 3);
  TTS_EQUAL(valuation(p3), 500); 
  TTS_EQUAL(valuation(sparse_polynom_t()), -1);
};
