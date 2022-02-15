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
EVE_TEST_TYPES( "Check return types of pi"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::pi(as<T>())  , T);
  TTS_EXPR_IS( eve::pi(as<v_t>()), v_t);
};

//==================================================================================================
// pi  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of pi on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;

  TTS_EQUAL(eve::pi(as<T>()), T(4*std::atan(1.0l)));
  TTS_EXPECT(eve::all(downward(eve::pi)(as<T>()) <= eve::pi(as<T>())));
  TTS_EXPECT(eve::all(eve::pi(as<T>()) <= upward(eve::pi)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::pi)(as<T>()), upward(eve::pi)(as<T>()), 0.5);
};
