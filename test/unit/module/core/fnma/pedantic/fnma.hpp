//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FNMA_HPP
#define FNMA_HPP

#include <eve/function/fnma.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check fnma return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::fnma)(Type()), Type);
}

TTS_CASE("Check eve::saturated_(eve::fnma) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::fnma)(Type{0}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::fnma)(Type{1}), Type(1));
  TTS_EQUAL(eve::saturated_(eve::fnma)(Type{2}), Type(2));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::fnma)(static_cast<Type>(-1)), Type(1));
    TTS_EQUAL(eve::saturated_(eve::fnma)(static_cast<Type>(-2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::fnma)(eve::Valmin<Type>()), eve::Valmax<Type>());
  }
}

#endif
