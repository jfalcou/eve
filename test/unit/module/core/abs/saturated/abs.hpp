//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/abs.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check abs return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::abs)(Type()), (Type));
}

TTS_CASE("Check eve::saturated_(eve::abs) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::abs)(Type{0}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::abs)(Type{1}), Type(1));
  TTS_EQUAL(eve::saturated_(eve::abs)(Type{2}), Type(2));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::abs)(static_cast<Type>(-1)), Type(1));
    TTS_EQUAL(eve::saturated_(eve::abs)(static_cast<Type>(-2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::abs)(eve::Valmin<Type>()), eve::Valmax<Type>());
  }
}
