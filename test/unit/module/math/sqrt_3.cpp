//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>
#include <iomanip>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sqrt_3"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::sqrt_3(as<T>())  , T);
  TTS_EXPR_IS( eve::sqrt_3(as<v_t>()), v_t);
};

//==================================================================================================
// sqrt_3  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of sqrt_3 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  if constexpr(sizeof(long double) > sizeof(elt_t))
  {
    using elt_t = eve::element_type_t<T>;
    TTS_EXPECT(downward(eve::sqrt_3)(as<elt_t>()) < std::sqrt(3.0l));
    TTS_EXPECT(upward(eve::sqrt_3)(as<elt_t>())   > std::sqrt(3.0l));
  }
  TTS_ULP_EQUAL(eve::sqrt_3(as<T>()), T(std::sqrt(3.0l)), 0.0);
  TTS_EXPECT(eve::all(downward(eve::sqrt_3)(as<T>()) <= eve::sqrt_3(as<T>())));
  TTS_EXPECT(eve::all(eve::sqrt_3(as<T>()) <= upward(eve::sqrt_3)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::sqrt_3)(as<T>()), upward(eve::sqrt_3)(as<T>()), 0.5);
};
