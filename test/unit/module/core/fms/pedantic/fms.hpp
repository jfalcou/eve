//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FMS_HPP
#define FMS_HPP

#include <eve/function/scalar/fms.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check fms return type")
{
  TTS_EXPR_IS(eve::saturated_(eve::fms)(Type()), Type);
}

TTS_CASE("Check eve::saturated_(eve::fms) behavior")
{
  TTS_EQUAL(eve::saturated_(eve::fms)(Type{0}), Type(0));
  TTS_EQUAL(eve::saturated_(eve::fms)(Type{1}), Type(1));
  TTS_EQUAL(eve::saturated_(eve::fms)(Type{2}), Type(2));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::saturated_(eve::fms)(static_cast<Type>(-1)), Type(1));
    TTS_EQUAL(eve::saturated_(eve::fms)(static_cast<Type>(-2)), Type(2));
    TTS_EQUAL(eve::saturated_(eve::fms)(eve::Valmin<Type>()), eve::Valmax<Type>());
  }
}

#endif
