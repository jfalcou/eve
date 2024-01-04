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
// third Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of third", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::third(as<T>()), T);
  TTS_EXPR_IS(eve::third(as<v_t>()), v_t);
};
//==================================================================================================
// third tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of third on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::third[eve::downward](eve::as<T>()) <= 1.0l/3);
    TTS_EXPECT(eve::third[eve::upward](eve::as<T>()) >= 1.0l/3); 
  }
  TTS_EQUAL(eve::third(eve::as<T>()), T(1.0l/3));
};

//==================================================================================================
// third  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of third on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::third[eve::downward](as<T>()), eve::third[eve::upward](as<T>()))));
};
