//revised
//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// pi2o_6 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of pi2o_6", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::pi2o_6(as<T>()), T);
  TTS_EXPR_IS(eve::pi2o_6(as<v_t>()), v_t);
};
//==================================================================================================
// pi2o_6 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of pi2o_6 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::pi2o_6[eve::downward](eve::as<T>()) <= 3.141592653589793238462643l*3.141592653589793238462643l/6);
    TTS_EXPECT(eve::pi2o_6[eve::upward](eve::as<T>()) >= 3.141592653589793238462643l*3.141592653589793238462643l/6);
  }
  TTS_EQUAL(eve::pi2o_6(eve::as<T>()), T(3.141592653589793238462643l*3.141592653589793238462643l/6));
};

//==================================================================================================
// pi2o_6  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of pi2o_6 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::pi2o_6[eve::downward](as<T>()), eve::pi2o_6[eve::upward](as<T>()))));
};
