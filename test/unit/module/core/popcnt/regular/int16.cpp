//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/popcnt.hpp>

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>

TTS_CASE("Check popcnt correctness on 16 bits signed integrals")
{
  using eve::popcnt;

  TTS_EQUAL(popcnt(std::int16_t{0}), 0);
  TTS_EQUAL(popcnt(std::numeric_limits<std::int16_t>::max()), 15);
  TTS_EQUAL(popcnt(std::numeric_limits<std::int16_t>::min()), 1);
}
