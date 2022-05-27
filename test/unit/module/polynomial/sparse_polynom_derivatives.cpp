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
EVE_TEST_TYPES( "Check behavior of derivative"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    using sparse_polynom_t = eve::sparse_polynom<elt_t>;
    polynom_t p0{1, 2, 0, 4, 0};
    sparse_polynom_t sp0(p0);
    polynom_t der(p0);
    sparse_polynom_t sder(sp0);
    auto ders = eve::derivative(sp0, 7u, eve::all);
    for(size_t i=0; i < 8u; ++i)
    {
      TTS_EXPECT(der == ders[i]);
      der = eve::derivative(der);
      sder = eve::derivative(sder);
      TTS_EXPECT(eve::derivative(sp0, i+1) == sparse_polynom_t(eve::derivative(p0, i+1)));
      TTS_EXPECT(sder == sparse_polynom_t(der));
    }
  } else TTS_PASS("");
};
