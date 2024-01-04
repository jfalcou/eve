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
// sqrtlog_4 Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of sqrtlog_4", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::sqrtlog_4(as<T>()), T);
  TTS_EXPR_IS(eve::sqrtlog_4(as<v_t>()), v_t);
};
//==================================================================================================
// sqrtlog_4 tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrtlog_4 on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::sqrtlog_4[eve::downward](eve::as<T>()) <= std::sqrt(std::log(4.0l)));
    TTS_EXPECT(eve::sqrtlog_4[eve::upward](eve::as<T>()) >= std::sqrt(std::log(4.0l))); 
  }
  TTS_EQUAL(eve::sqrtlog_4(eve::as<T>()), T(std::sqrt(std::log(4.0l))));
};

//==================================================================================================
// sqrtlog_4  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of sqrtlog_4 on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::sqrtlog_4[eve::downward](as<T>()), eve::sqrtlog_4[eve::upward](as<T>()))));
};
