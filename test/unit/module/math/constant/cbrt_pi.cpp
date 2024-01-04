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
// cbrt_pi Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of cbrt_pi", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::cbrt_pi(as<T>()), T);
  TTS_EXPR_IS(eve::cbrt_pi(as<v_t>()), v_t);
};
//==================================================================================================
// cbrt_pi tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of cbrt_pi on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::cbrt_pi[eve::downward](eve::as<T>()) <= std::cbrt(3.141592653589793238462643l));
    TTS_EXPECT(eve::cbrt_pi[eve::upward](eve::as<T>()) >= std::cbrt(3.141592653589793238462643l));
  }
  TTS_EQUAL(eve::cbrt_pi(eve::as<T>()), T(std::cbrt(3.141592653589793238462643l)));
};

//==================================================================================================
// cbrt_pi  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of cbrt_pi on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::cbrt_pi[eve::downward](as<T>()), eve::cbrt_pi[eve::upward](as<T>()))));
};
