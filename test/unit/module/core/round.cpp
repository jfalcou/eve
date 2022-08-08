//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of round", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::round(T()), T);
  TTS_EXPR_IS(eve::round(v_t()), v_t);
  TTS_EXPR_IS(eve::upward(eve::round)(T()), T);
  TTS_EXPR_IS(eve::downward(eve::round)(T()), T);
  TTS_EXPR_IS(eve::toward_zero(eve::round)(T()), T);
  TTS_EXPR_IS(eve::to_nearest(eve::round)(T()), T);
};

//==================================================================================================
// round(simd)  tests
//==================================================================================================
TTS_CASE_TPL("Check behavior of round(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::upward(eve::round)(T(1.7)), eve::ceil(T(1.7)));
  TTS_EQUAL(eve::downward(eve::round)(T(1.7)), eve::floor(T(1.7)));
  TTS_EQUAL(eve::toward_zero(eve::round)(T(1.7)), eve::trunc(T(1.7)));
  TTS_EQUAL(eve::to_nearest(eve::round)(T(1.7)), eve::nearest(T(1.7)));
  TTS_EQUAL(eve::round(T(1.7)), eve::nearest(T(1.7)));

  TTS_EQUAL(eve::upward(eve::round)(T(1.3)), eve::ceil(T(1.3)));
  TTS_EQUAL(eve::downward(eve::round)(T(1.3)), eve::floor(T(1.3)));
  TTS_EQUAL(eve::toward_zero(eve::round)(T(1.3)), eve::trunc(T(1.3)));
  TTS_EQUAL(eve::to_nearest(eve::round)(T(1.3)), eve::nearest(T(1.3)));
  TTS_EQUAL(eve::round(T(1.3)), eve::nearest(T(1.3)));
};
