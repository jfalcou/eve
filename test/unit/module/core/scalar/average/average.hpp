//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include <eve/function/scalar/average.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <type_traits>


TTS_CASE("Check eve::average behavior")
{
  TTS_EQUAL(eve::average(Type{0}, Type{0}), Type{0});
  TTS_EQUAL(eve::average(Type{0}, Type{2}), Type{1});
  TTS_EQUAL(eve::average(Type{2}, Type{0}), Type{1});
  TTS_EQUAL(eve::average(Type{1}, Type{1}), Type{1});
}

#endif
