//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/saturated.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturated_(eve::sqr) return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::sqr)(Type(0)), (Type));
}

TTS_CASE("Check eve::sqr behavior")
{
  TTS_EQUAL(eve::saturated_(eve::sqr)(Type(1)), (Type(1)));
  TTS_EQUAL(eve::saturated_(eve::sqr)(Type(2)), (Type(4)));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::sqr)(static_cast<Type>(-2)), (Type(4)));
  }

  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::saturated_(eve::sqr)(eve::Mzero<Type>()), (Type(0)));
  }

  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::sqr)(eve::inc(eve::Sqrtvalmax<Type>())), eve::Valmax<Type>());
  }
}
