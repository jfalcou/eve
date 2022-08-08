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
<typename T>(tts::type<T>) { TTS_EXPR_IS(eve::saturate(T(), eve::as<std::int8_t>()), T); };

TTS_CASE_TPL("Check eve::saturate behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int8_t>()),
              T(eve::valmin(eve::as<std::int8_t>())));
  }
  else { TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int8_t>()), T(0)); }

  TTS_EQUAL(eve::saturate(T(0), eve::as<std::int8_t>()), T(0));
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<std::int8_t>()), T(42.69));
  TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::int8_t>()),
            T(eve::valmax(eve::as<std::int8_t>())));
};
