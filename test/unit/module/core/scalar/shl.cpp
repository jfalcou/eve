//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/shl.hpp>
#include <tts/tts.hpp> 
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check shl return type")
{
  TTS_EXPR_IS(eve::shl(0.f, 0), float);
  TTS_EXPR_IS(eve::shl(0., 0), double);
  TTS_EXPR_IS(eve::shl(0.f, std::int32_t()), float);
  TTS_EXPR_IS(eve::shl(0., std::int64_t()), double);

  TTS_EXPR_IS(eve::shl(std::int8_t(), std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::shl(std::int16_t(), std::int16_t()), std::int16_t);
  TTS_EXPR_IS(eve::shl(std::int32_t(), std::int32_t()), std::int32_t);
  TTS_EXPR_IS(eve::shl(std::int64_t(), std::int64_t()), std::int64_t);

  TTS_EXPR_IS(eve::shl(std::uint8_t(), std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::shl(std::uint16_t(), std::uint16_t()), std::uint16_t);
  TTS_EXPR_IS(eve::shl(std::uint32_t(), std::uint32_t()), std::uint32_t);
  TTS_EXPR_IS(eve::shl(std::uint64_t(), std::uint64_t()), std::uint64_t);
}

TTS_CASE("Check shl behavior")
{
  TTS_EQUAL(eve::shl(std::uint8_t(3), 4),std::uint8_t(48));
  TTS_EQUAL(eve::shl(std::uint16_t(3), 4),std::uint16_t(48));
  TTS_EQUAL(eve::shl(std::uint32_t(3), 4),std::uint32_t(48));
  TTS_EQUAL(eve::shl(std::uint64_t(3), 4),std::uint64_t(48));
  TTS_EQUAL(eve::shl(std::int8_t(3), 4),std::int8_t(48));
  TTS_EQUAL(eve::shl(std::int16_t(3), 4),std::int16_t(48));
  TTS_EQUAL(eve::shl(std::int32_t(3), 4),std::int32_t(48));
  TTS_EQUAL(eve::shl(std::int64_t(3), 4),std::int64_t(48));
  
  TTS_IEEE_EQUAL(eve::shl(-1.5f, 4), -0x1p+121);
  TTS_IEEE_EQUAL(eve::shl(-4.753, 4), 0x1.03126e978d5p-1004);
}
