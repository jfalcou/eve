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
<typename T>(tts::type<T>) { TTS_EXPR_IS(eve::saturate(T(), eve::as<std::uint32_t>()), T); };

TTS_CASE_TPL("Check eve::saturate behavior", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::saturate(T(0), eve::as<std::uint32_t>()), T(0));
  TTS_EQUAL(eve::saturate(T(42.69), eve::as<std::uint32_t>()), T(42.69));

  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::saturate(eve::valmin(eve::as<T>()), eve::as<std::uint32_t>()), T(0));
    TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint32_t>()),
              T(eve::valmax(eve::as<std::uint32_t>())));
  }
  else
  {
    if constexpr( eve::signed_value<T> )
    {
      using v_t = eve::element_type_t<T>;

      if constexpr( sizeof(v_t) <= sizeof(std::int32_t) )
      {
        TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint32_t>()),
                  eve::valmax(eve::as<T>()));
      }
      else
      {
        TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint32_t>()),
                  T(eve::valmax(eve::as<std::uint32_t>())));
      }
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::valmax(eve::as<T>()), eve::as<std::uint32_t>()),
                T(eve::valmax(eve::as<std::uint32_t>())));
    }
  }
};
