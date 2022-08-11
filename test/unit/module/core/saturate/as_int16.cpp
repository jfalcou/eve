//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::saturate return type", eve::test::simd::all_types)
<typename T>(tts::type<T>) { TTS_EXPR_IS(eve::saturate(T(), eve::as<std::int16_t>()), T); };

TTS_CASE_TPL("Check eve::saturate behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr( eve::signed_value<T> )
  {
    using v_t = eve::element_type_t<T>;
    if constexpr( sizeof(v_t) < sizeof(std::int16_t) )
    {
      TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int16_t>()),
                eve::valmin(eve::as<T>()));
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int16_t>()),
                T(eve::valmin(eve::as<std::int16_t>())));
    }
  }
  else { TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::int16_t>()), T(0)); }

  TTS_EQUAL(eve::saturate(T(0), eve::as<std::int16_t>()), T(0));
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<std::int16_t>()), T(42.69));

  using v_t = eve::element_type_t<T>;
  if constexpr( sizeof(v_t) < sizeof(std::int16_t) )
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::int16_t>()),
              eve::valmax(eve::as<T>()));
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::int16_t>()),
              T(eve::valmax(eve::as<std::int16_t>())));
  }
};
