//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/scalar/popcnt.hpp>

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE("Check popcnt correctness on 16 bits unsigned integrals")
{
  using eve::popcnt;

  TTS_EQUAL(popcnt(std::uint16_t{0}), 0);
  TTS_EQUAL(popcnt(std::uint16_t{65535}), 16);
  TTS_EQUAL(popcnt(std::uint16_t{0b1010101010101010}), 8);
}
