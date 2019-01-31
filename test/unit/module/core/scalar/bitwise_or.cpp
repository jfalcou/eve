//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/bitwise_and.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check bitwise_and return type")
{
  TTS_EXPR_IS(eve::bitwise_and(0.f, 0.f), float);
  TTS_EXPR_IS(eve::bitwise_and(0., 0.), double);
  TTS_EXPR_IS(eve::bitwise_and(0.f, std::int32_t()), float);
  TTS_EXPR_IS(eve::bitwise_and(0., std::int64_t()), double);
  TTS_EXPR_IS(eve::bitwise_and(std::int32_t(), 0.f), std::int32_t);
  TTS_EXPR_IS(eve::bitwise_and(std::int64_t(), 0.), std::int64_t);

  TTS_EXPR_IS(eve::bitwise_and(std::int8_t(), std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::bitwise_and(std::int16_t(), std::int16_t()), std::int16_t);
  TTS_EXPR_IS(eve::bitwise_and(std::int32_t(), std::int32_t()), std::int32_t);
  TTS_EXPR_IS(eve::bitwise_and(std::int64_t(), std::int64_t()), std::int64_t);

  TTS_EXPR_IS(eve::bitwise_and(std::uint8_t(), std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::bitwise_and(std::uint16_t(), std::uint16_t()), std::uint16_t);
  TTS_EXPR_IS(eve::bitwise_and(std::uint32_t(), std::uint32_t()), std::uint32_t);
  TTS_EXPR_IS(eve::bitwise_and(std::uint64_t(), std::uint64_t()), std::uint64_t);
}

TTS_CASE("Check bitwise_and behavior")
{
  TTS_EQUAL(eve::bitwise_and(std::uint8_t(0b01000011), std::uint8_t(0b01011010)),
            std::uint8_t(0b01000010));

  TTS_EQUAL(eve::bitwise_and(std::uint16_t(0b1100001101000011), std::uint16_t(0b0111010101011010)),
            std::uint16_t(0b0100000101000010));

  TTS_EQUAL(eve::bitwise_and(-1.5f, 0x7FFFFFFFU), 1.5f);
  TTS_EQUAL(eve::bitwise_and(-4.753, 0x7FFFFFFFFFFFFFFFUL), 4.753);
}
