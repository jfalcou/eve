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

TTS_CASE("Check popcnt correctness on 8 bits signed integrals")
{
  using eve::popcnt;

  TTS_EQUAL(popcnt(std::int8_t{0}), 0);
  TTS_EQUAL(popcnt(std::numeric_limits<std::int8_t>::max()), 7);
  TTS_EQUAL(popcnt(std::numeric_limits<std::int8_t>::min()), 1);
}
