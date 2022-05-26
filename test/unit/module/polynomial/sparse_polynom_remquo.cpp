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
EVE_TEST_TYPES( "Check behavior of remquo"
        , eve::test::simd::ieee_reals
        )
  <typename T>(eve::as<T>)
{
  if constexpr(eve::cardinal_v<T> == 1)
  {
    using elt_t = eve::element_type_t<T>;
    using polynom_t = eve::polynom<elt_t>;
    using sparse_polynom_t = eve::sparse_polynom<elt_t>;
    polynom_t p0{1, 2, 3, 4, 5};
    polynom_t p1{1, 0, 2};
    sparse_polynom_t sp1(p1);
    sparse_polynom_t sp0(p0);
    {
      auto [r, q] = remquo(p0, p1);
      auto [sr, sq] = remquo(sp0, sp1);
      TTS_EXPECT(q == sq);
      TTS_EXPECT(r == sr);
    }
  } else TTS_PASS("");
};
