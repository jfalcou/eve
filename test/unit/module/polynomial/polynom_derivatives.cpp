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
EVE_TEST_TYPES( "Check behavior of derivatives"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  using elt_t = eve::element_type_t<T>;
  using polynom_t = eve::polynom<elt_t>;
  std::vector<elt_t> const c0{1, 2, 3, 4, 5};
  polynom_t const p0(c0);
  auto der = p0;
//  auto ders = p0.derivatives(7u);
  for(size_t i=0; i < 8u; ++i)
  {
    inplace(derivative)(der);
    der = derivative(der);
    std::cout << der << std::endl;
//    TTS_EXPECT(der == p0.derivative(i));
  }
};
