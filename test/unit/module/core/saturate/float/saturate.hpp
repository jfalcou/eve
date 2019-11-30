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
#include <eve/function/convert.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturate return type")
{
  TTS_EXPR_IS(eve::saturate((Type()), eve::as<float>()), (Type));
  TTS_EXPR_IS(eve::saturate((Type()), eve::single_    ), (Type));
}
 
TTS_CASE("Check eve::saturate behavior")
{
  TTS_EQUAL(eve::saturate((Type(42.69)),       eve::single_), (Type(42.69)) );
  TTS_EQUAL(eve::saturate((Type(0))    ,       eve::single_), (Type(0))     );
  if constexpr(std::is_same_v<Value, double>)
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<Type>(), eve::single_), (Type(eve::Valmax<float>()))); 
    TTS_EQUAL(eve::saturate(eve::Valmin<Type>(), eve::single_), (Type(eve::Valmin<float>())));
  }
  else
  {
    TTS_EQUAL(eve::saturate(eve::Valmax<Type>(), eve::single_), (eve::Valmax<Type>())); 
    TTS_EQUAL(eve::saturate(eve::Valmin<Type>(), eve::single_), (eve::Valmin<Type>()));
  }
}
