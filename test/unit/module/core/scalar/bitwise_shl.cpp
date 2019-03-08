//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/bitwise_shl.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check bitwise_shl return type")
{

  TTS_EXPR_IS(eve::bitwise_shl(std::int8_t(), std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::bitwise_shl(std::int16_t(), std::int16_t()), std::int16_t);
  TTS_EXPR_IS(eve::bitwise_shl(std::int32_t(), std::int32_t()), std::int32_t);
  TTS_EXPR_IS(eve::bitwise_shl(std::int64_t(), std::int64_t()), std::int64_t);

  TTS_EXPR_IS(eve::bitwise_shl(std::uint8_t(), std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::bitwise_shl(std::uint16_t(), std::uint16_t()), std::uint16_t);
  TTS_EXPR_IS(eve::bitwise_shl(std::uint32_t(), std::uint32_t()), std::uint32_t);
  TTS_EXPR_IS(eve::bitwise_shl(std::uint64_t(), std::uint64_t()), std::uint64_t);
}

TTS_CASE("Check bitwise_shl behavior")
{
  TTS_EQUAL(eve::bitwise_shl(std::uint8_t(3), 4), std::uint8_t(48));
  TTS_EQUAL(eve::bitwise_shl(std::uint16_t(3), 4), std::uint16_t(48));
  TTS_EQUAL(eve::bitwise_shl(std::uint32_t(3), 4), std::uint32_t(48));
  TTS_EQUAL(eve::bitwise_shl(std::uint64_t(3), 4), std::uint64_t(48));
  TTS_EQUAL(eve::bitwise_shl(std::int8_t(3), 4), std::int8_t(48));
  TTS_EQUAL(eve::bitwise_shl(std::int16_t(3), 4), std::int16_t(48));
  TTS_EQUAL(eve::bitwise_shl(std::int32_t(3), 4), std::int32_t(48));
  TTS_EQUAL(eve::bitwise_shl(std::int64_t(3), 4), std::int64_t(48));
}
