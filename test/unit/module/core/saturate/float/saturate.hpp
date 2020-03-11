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
#include <eve/function/convert.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturate return type")
{
  TTS_EXPR_IS(eve::saturate((EVE_TYPE()), eve::as<float>()), (EVE_TYPE));
  TTS_EXPR_IS(eve::saturate((EVE_TYPE()), eve::single_    ), (EVE_TYPE));
}
 
TTS_CASE("Check eve::saturate behavior")
{
  TTS_EQUAL(eve::saturate((EVE_TYPE(42.69)),       eve::single_), (EVE_TYPE(42.69)) );
  TTS_EQUAL(eve::saturate((EVE_TYPE(0))    ,       eve::single_), (EVE_TYPE(0))     );
  if constexpr(std::is_same_v<EVE_VALUE, double>)
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<EVE_TYPE>(), eve::single_), (EVE_TYPE(eve::Valmax<float>()))); 
    TTS_EQUAL(eve::saturate(eve::Valmin<EVE_TYPE>(), eve::single_), (EVE_TYPE(eve::Valmin<float>())));
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<EVE_TYPE>(), eve::single_), (eve::Valmax<EVE_TYPE>())); 
    TTS_EQUAL(eve::saturate(eve::Valmin<EVE_TYPE>(), eve::single_), (eve::Valmin<EVE_TYPE>()));
  }
}
