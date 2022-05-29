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
EVE_TEST( "Check behavior of sparse_polynom evaluation"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, 10.0))
        )
<typename T>(T const& x)
{
  using elt_t = eve::element_type_t<T>;
  using polynom_t = eve::polynom<elt_t>;
  using sparse_polynom_t = eve::sparse_polynom<elt_t>;
  std::vector<elt_t> const c0{0, 1, 0, 3, 0, 5, 0, 7, 0, 9};
  polynom_t p0(c0);
  sparse_polynom_t sp0(p0);
  TTS_ULP_EQUAL(p0(x), sp0(x), 2);
};
