//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturate.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturate return type")
{
  TTS_EXPR_IS(eve::saturate( (EVE_TYPE()),  eve::as<std::int16_t>()), (EVE_TYPE));
  TTS_EXPR_IS(eve::saturate( (EVE_TYPE()),  eve::int16_            ), (EVE_TYPE));
}

TTS_CASE("Check eve::saturate behavior")
{
  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    if constexpr(sizeof(EVE_VALUE) < sizeof(std::int16_t))
    {
      TTS_EQUAL(eve::saturate( eve::Valmin<EVE_TYPE>(), eve::int16_), eve::Valmin<EVE_TYPE>() );
    }
    else
    {
      TTS_EQUAL(eve::saturate(eve::Valmin<EVE_TYPE>(), eve::int16_), (EVE_TYPE(eve::Valmin<std::int16_t>())) );
    }
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmin<EVE_TYPE>(), eve::int16_), (EVE_TYPE(0)) );
  }

  TTS_EQUAL(eve::saturate((EVE_TYPE(0))    , eve::int16_      ), (EVE_TYPE(0))     );
  TTS_EQUAL(eve::saturate((EVE_TYPE(42.69)), eve::int16_      ), (EVE_TYPE(42.69)) );

  if constexpr(sizeof(EVE_VALUE) < sizeof(std::int16_t))
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<EVE_TYPE>(), eve::int16_), eve::Valmax<EVE_TYPE>() );
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<EVE_TYPE>(), eve::int16_), (EVE_TYPE(eve::Valmax<std::int16_t>())) );
  }
}
