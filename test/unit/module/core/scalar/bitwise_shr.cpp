//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/bitwise_shr.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check bitwise_shr return type")
{

  TTS_EXPR_IS(eve::bitwise_shr(std::int8_t(), std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::bitwise_shr(std::int16_t(), std::int16_t()), std::int16_t);
  TTS_EXPR_IS(eve::bitwise_shr(std::int32_t(), std::int32_t()), std::int32_t);
  TTS_EXPR_IS(eve::bitwise_shr(std::int64_t(), std::int64_t()), std::int64_t);

  TTS_EXPR_IS(eve::bitwise_shr(std::uint8_t(), std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::bitwise_shr(std::uint16_t(), std::uint16_t()), std::uint16_t);
  TTS_EXPR_IS(eve::bitwise_shr(std::uint32_t(), std::uint32_t()), std::uint32_t);
  TTS_EXPR_IS(eve::bitwise_shr(std::uint64_t(), std::uint64_t()), std::uint64_t);
}

TTS_CASE("Check bitwise_shr behavior")
{
  TTS_EQUAL(eve::bitwise_shr(std::uint8_t(64), 4),std::uint8_t(4));
  TTS_EQUAL(eve::bitwise_shr(std::uint16_t(64), 4),std::uint16_t(4));
  TTS_EQUAL(eve::bitwise_shr(std::uint32_t(64), 4),std::uint32_t(4));
  TTS_EQUAL(eve::bitwise_shr(std::uint64_t(64), 4),std::uint64_t(4));
  TTS_EQUAL(eve::bitwise_shr(std::int8_t(64), 4),std::int8_t(4));
  TTS_EQUAL(eve::bitwise_shr(std::int16_t(64), 4),std::int16_t(4));
  TTS_EQUAL(eve::bitwise_shr(std::int32_t(64), 4),std::int32_t(4));
  TTS_EQUAL(eve::bitwise_shr(std::int64_t(64), 4),std::int64_t(4));
  TTS_EQUAL(eve::bitwise_shr(std::int8_t(-64), 4),std::int8_t(12));
  TTS_EQUAL(eve::bitwise_shr(std::int16_t(-64), 4),std::int16_t(4092));
  TTS_EQUAL(eve::bitwise_shr(std::int32_t(-64), 4),std::int32_t(268435452));
  TTS_EQUAL(eve::bitwise_shr(std::int64_t(-64), 4),std::int64_t(1152921504606846972LL));

}
