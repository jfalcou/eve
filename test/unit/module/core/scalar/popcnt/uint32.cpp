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

TTS_CASE("Check popcnt correctness on 32 bits unsigned integrals")
{
  using eve::popcnt;

  TTS_EQUAL(popcnt(std::uint32_t{0}), 0UL);
  TTS_EQUAL(popcnt(std::uint32_t{0xFFFFFFFF}), 32UL);
  TTS_EQUAL(popcnt(std::uint32_t{0xAAAAAAAA}), 16UL);
}
