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
// khinchin Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of khinchin", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::khinchin(as<T>()), T);
  TTS_EXPR_IS(eve::khinchin(as<v_t>()), v_t);
};
//==================================================================================================
// khinchin tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of khinchin on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::khinchin[eve::downward](eve::as<T>()) <=2.685452001065306445309714 );
    TTS_EXPECT(eve::khinchin[eve::upward](eve::as<T>()) >= 2.685452001065306445309714);
  }
  TTS_EQUAL(eve::khinchin(eve::as<T>()), T(2.685452001065306445309714));
};

//==================================================================================================
// khinchin  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of khinchin on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::khinchin[eve::downward](as<T>()), eve::khinchin[eve::upward](as<T>()))));
};
