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
EVE_TEST_TYPES( "Check return types of log_2"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS( eve::log_2(as<T>())  , T);
  TTS_EXPR_IS( eve::log_2(as<v_t>()), v_t);
};

//==================================================================================================
// log_2  tests
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of log_2 on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  using eve::as;
  using eve::downward;
  using eve::upward;
  std::cout << (eve::log_2(as<float>()) <  std::log(2.0l)) << std::endl;
  std::cout << (eve::log_2(as<double>()) < std::log(2.0l)) << std::endl;
  TTS_ULP_EQUAL(eve::log_2(as<T>()), T(std::log(2.0l)), 0.0);
  TTS_EXPECT(eve::all(downward(eve::log_2)(as<T>()) <= eve::log_2(as<T>())));
  TTS_EXPECT(eve::all(eve::log_2(as<T>()) <= upward(eve::log_2)(as<T>())));
  TTS_ULP_EQUAL(downward(eve::log_2)(as<T>()), upward(eve::log_2)(as<T>()), 0.5);
};
