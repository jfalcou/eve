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
EVE_TEST_TYPES( "Check behavior of coefs"
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
    std::vector<elt_t> c{1, 2, 4};
    std::vector<int  > e{4, 3, 1};
    sparse_polynom_t sp0(p0);
    auto   eq = [](auto v1, auto v2){
      if (v1.size()!=  v2.size()) return false;
      for(size_t i=0; i < v1.size(); ++i) if (v1[i]!= v2[i]) return false;
      return true;
    };
    TTS_EXPECT(eq(eve::coefs(p0), c));
    TTS_EXPECT(eq(eve::coefs(sp0), c));
    TTS_EXPECT(eq(eve::exponents(p0), e));
    TTS_EXPECT(eq(eve::exponents(sp0), e));
  } else TTS_PASS("");
};
