//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DIV_HPP
#define DIV_HPP

#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/function/div.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE( "Check div return type" )
{
  TTS_EXPR_IS(eve::saturated_(eve::div[Type()])( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::saturated_(eve::div[eve::logical<Type>()])( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::saturated_(eve::div[true])( Type(), Type() ) , Type );
}

TTS_CASE("Check eve::saturated_(eve::div) behavior")
{
  if constexpr(std::is_integral_v<Type>)
  {
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Mone<Type>(), eve::Mone<Type>()), eve::One<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Valmax<Type>(),eve::Mone<Type>()), eve::Valmin<Type>()+eve::One<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Valmax<Type>(),eve::One<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Valmin<Type>(),eve::Mone<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Mone<Type>(), eve::Zero<Type>()), eve::Valmin<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(Type(-2), eve::Zero<Type>()), eve::Valmin<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Valmin<Type>(), eve::Zero<Type>()), eve::Valmin<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::One<Type>(), eve::Zero<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(Type(2), eve::Zero<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Valmax<Type>(), eve::Zero<Type>()), eve::Valmax<Type>());
    }
    else
    {
      TTS_EQUAL(eve::saturated_(eve::div)(eve::One<Type>(), eve::One<Type>()), eve::One<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Valmax<Type>(),eve::One<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::One<Type>(), eve::Zero<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(Type(2), eve::Zero<Type>()), eve::Valmax<Type>());
      TTS_EQUAL(eve::saturated_(eve::div)(eve::Valmax<Type>(), eve::Zero<Type>()), eve::Valmax<Type>());
    }
  }
  else
  {
    TTS_EQUAL(eve::saturated_(eve::div)(Type{0} , Type{1}), Type{0});
    TTS_EQUAL(eve::saturated_(eve::div)(Type{1} , Type{1}), Type{1});
    TTS_EQUAL(eve::saturated_(eve::div)(Type{12}, Type{4}), Type{3});
    TTS_EQUAL(eve::saturated_(eve::div)(Type{1} , Type{2}), Type(0.5));
  }
}

#endif
