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

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sqrteps"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::sqrteps(as<T>())  , T);
  TTS_EXPR_IS( eve::sqrteps(as<v_t>()), v_t);
};

//==================================================================================================
// sqrteps  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of sqrteps on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  TTS_EQUAL(eve::sqrteps(as<T>()), T(std::sqrt(eve::eps(as<eve::element_type_t<T>>()))));
  TTS_EXPECT(eve::all(downward(eve::sqrteps)(as<T>()) <= eve::sqrteps(as<T>())));
  TTS_EXPECT(eve::all(eve::sqrteps(as<T>()) <= upward(eve::sqrteps)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::sqrteps)(as<T>()), upward(eve::sqrteps)(as<T>()), 0.5);
};
