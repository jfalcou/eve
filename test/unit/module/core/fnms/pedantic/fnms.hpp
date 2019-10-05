//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FNMS_HPP
#define FNMS_HPP

#include <eve/function/fnms.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check fnms return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::fnms)(Type()), Type);
}

TTS_CASE("Check eve::saturated_(eve::fnms) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::fnms)(Type{0}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::fnms)(Type{1}), Type(1));
  TTS_EQUAL(eve::saturated_(eve::fnms)(Type{2}), Type(2));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::fnms)(static_cast<Type>(-1)), Type(1));
    TTS_EQUAL(eve::saturated_(eve::fnms)(static_cast<Type>(-2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::fnms)(eve::Valmin<Type>()), eve::Valmax<Type>());
  }
}

#endif
