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
EVE_TEST_TYPES( "Check behavior of primitive"
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
    polynom_t prim(p0);
    sparse_polynom_t sprim(sp0);
    auto prims = eve::primitive(sp0, 7u, eve::all);
    for(size_t i=0; i < 8u; ++i)
    {
      TTS_EXPECT((eve::dist(prims[i], prim) < eve::eps(eve::as<elt_t>())));
      std::cout << "i " << i << std::endl;
      prim = eve::primitive(prim);
      sprim = eve::primitive(sprim);
      auto z = eve::dist(eve::primitive(sp0, i+1), sparse_polynom_t(eve::primitive(p0, i+1)));
      std::cout << (z < eve::eps(eve::as<elt_t>())) << std::endl;
      TTS_EXPECT((eve::dist(eve::primitive(sp0, i+1), sparse_polynom_t(eve::primitive(p0, i+1))) < eve::eps(eve::as<elt_t>())));
      TTS_EXPECT(sprim == sparse_polynom_t(prim));
    }
  } else TTS_PASS("");
};
