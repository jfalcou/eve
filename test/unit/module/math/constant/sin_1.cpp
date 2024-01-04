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
// sin_1 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sin_1", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sin_1(as<T>()), T);
  TTS_EXPR_IS(eve::sin_1(as<v_t>()), v_t);
};
//==================================================================================================
// sin_1 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of sin_1 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::sin_1[eve::downward](eve::as<T>()) <= std::sin(1.0l));
    TTS_EXPECT(eve::sin_1[eve::upward](eve::as<T>()) >= std::sin(1.0l)); 
  }
  TTS_EQUAL(eve::sin_1(eve::as<T>()), T(std::sin(1.0l)));
};

//==================================================================================================
// sin_1  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of sin_1 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::sin_1[eve::downward](as<T>()), eve::sin_1[eve::upward](as<T>()))));
};
