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

TTS_CASE("Check popcnt correctness on 64 bits unsigned integrals")
{
  using eve::popcnt;

  TTS_EQUAL(popcnt(std::uint64_t{0}), 0ULL);
  TTS_EQUAL(popcnt(std::uint64_t{0xFFFFFFFFFFFFFFFFULL}), 64ULL);
  TTS_EQUAL(popcnt(std::uint64_t{0xAAAAAAAAAAAAAAAAULL}), 32ULL);
}
