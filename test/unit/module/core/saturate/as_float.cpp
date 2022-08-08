//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::saturate return type", eve::test::simd::all_types)
<typename T>(tts::type<T>) { TTS_EXPR_IS(eve::saturate(T(), eve::as<float>()), T); };

TTS_CASE_TPL("Check eve::saturate behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<float>()), T(42.69));
  TTS_EQUAL(eve::saturate(T(0), eve::as<float>()), T(0));

  using v_t = eve::element_type_t<T>;

  if constexpr( std::is_same_v<v_t, double> )
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<float>()),
              T(eve::valmax(eve::as<float>())));
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<float>()),
              T(eve::valmin(eve::as<float>())));
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<float>()),
              eve::valmax(eve::as<T>()));
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<float>()),
              eve::valmin(eve::as<T>()));
  }
};
