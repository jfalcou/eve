//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of ulpdist", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::ulpdist(T(), T()), T);
  TTS_EXPR_IS(eve::ulpdist(T(), v_t()), T);
  TTS_EXPR_IS(eve::ulpdist(v_t(), T()), T);
  TTS_EXPR_IS(eve::ulpdist(v_t(), v_t()), v_t);
};

TTS_CASE_TPL("Check return types of ulpdist", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::ulpdist;
  TTS_EXPR_IS(ulpdist(T(), T()), T);

  if constexpr( eve::floating_value<T> )
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_EQUAL(ulpdist(eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), T(0));
      TTS_EQUAL(ulpdist(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), T(0));
      TTS_EQUAL(ulpdist(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())), T(0));
    }

    TTS_EQUAL(ulpdist(T(1), eve::inc(eve::eps(as<T>()))), T(0.5));
    TTS_EQUAL(ulpdist(T(1), T(-eve::dec(eve::eps(as<T>())))), T(1));
    TTS_EQUAL(ulpdist(T(1), T(-eve::dec(eve::eps(as<T>()) / 2))), T(0.5));
  }

  TTS_EQUAL(ulpdist(T(-1), T(-1)), T(0));
  TTS_EQUAL(ulpdist(T(1), T(1)), T(0));
  TTS_EQUAL(ulpdist(T(0), T(0)), T(0));
};
