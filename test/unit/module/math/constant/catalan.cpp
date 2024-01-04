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
// catalan Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of catalan", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::catalan(as<T>()), T);
  TTS_EXPR_IS(eve::catalan(as<v_t>()), v_t);
};
//==================================================================================================
// catalan tests on scalar
//==================================================================================================
TTS_CASE_TPL("Check behavior of catalan on scalar", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  if constexpr( sizeof(long double) > sizeof(T) )
  {
    TTS_EXPECT(eve::catalan[eve::downward](eve::as<T>()) <= 0.915965594177219015054603l);
    TTS_EXPECT(eve::catalan[eve::upward](eve::as<T>()) >= 0.915965594177219015054603l);
  }
  TTS_EQUAL(eve::catalan(eve::as<T>()), T(0.915965594177219015054603l));
};

//==================================================================================================
// catalan  tests on wide
//==================================================================================================
TTS_CASE_TPL("Check behavior of catalan on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using eve::as;
  TTS_EXPECT(eve::all(eve::test::is_near(eve::catalan[eve::downward](as<T>()), eve::catalan[eve::upward](as<T>()))));
};
