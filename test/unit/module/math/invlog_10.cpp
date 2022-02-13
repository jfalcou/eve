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
EVE_TEST_TYPES( "Check return types of invlog10"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::invlog_10(as<T>())  , T);
  TTS_EXPR_IS( eve::invlog_10(as<v_t>()), v_t);
};

//==================================================================================================
// invlog_10  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of invlog_10 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  TTS_ULP_EQUAL(eve::invlog_10(as<T>()), T(1)/T(eve::log(10.0)), 0.0);
  TTS_EXPECT(eve::all(downward(eve::invlog_10)(as<T>()) <= eve::invlog_10(as<T>())));
  TTS_EXPECT(eve::all(eve::invlog_10(as<T>()) <= upward(eve::invlog_10)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::invlog_10)(as<T>()), upward(eve::invlog_10)(as<T>()), 0.5);
};
