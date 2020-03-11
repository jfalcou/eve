//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
  TTS_EXPR_IS(eve::saturate((EVE_TYPE()), eve::as<std::int8_t>()), (EVE_TYPE));
  TTS_EXPR_IS(eve::saturate((EVE_TYPE()), eve::int8_            ), (EVE_TYPE));
}

TTS_CASE("Check eve::saturate behavior")
{
  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::saturate(eve::Valmin<EVE_TYPE>(), eve::int8_), (EVE_TYPE(eve::Valmin<std::int8_t>())) );
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmin<EVE_TYPE>(), eve::int8_), (EVE_TYPE(0)) );
  }
  
  TTS_EQUAL(eve::saturate((EVE_TYPE(0)), eve::int8_          ), (EVE_TYPE(0))     );
  TTS_EQUAL(eve::saturate((EVE_TYPE(42.69)), eve::int8_       ), (EVE_TYPE(42.69)) );
  TTS_EQUAL(eve::saturate(eve::Valmax<EVE_TYPE>(), eve::int8_), (EVE_TYPE(eve::Valmax<std::int8_t>())) );
}
