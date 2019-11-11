//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/inc.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check inc return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::inc)(Type()), (Type));
}

TTS_CASE("Check saturated_(inc) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::inc)(eve::Valmax<Type>()), eve::Valmax<Type>());
  TTS_EQUAL(eve::saturated_(eve::inc)(Type(1)), (Type(2)));
  TTS_EQUAL(eve::saturated_(eve::inc)(Type(2)), (Type(3)));

if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::inc)(Type(-2)), (Type(-1)));
  }

  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::inc)( eve::Mzero<Type>()), (Type(1)));
    TTS_EQUAL(eve::saturated_(eve::inc)( (Type(0))         ), (Type(1)));
  }
}
