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
// quarter Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of quarter", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::quarter(as<T>()), T);
  TTS_EXPR_IS(eve::quarter(as<v_t>()), v_t);
};
//==================================================================================================
// quarter tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of quarter on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::quarter[eve::downward](eve::as<T>()) <= 0.25l);
    TTS_EXPECT(eve::quarter[eve::upward](eve::as<T>()) >= 0.25l); 
  }
  TTS_EQUAL(eve::quarter(eve::as<T>()), T(0.25l));
};

//==================================================================================================
// quarter  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of quarter on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::quarter[eve::downward](as<T>()), eve::quarter[eve::upward](as<T>()))));
};
