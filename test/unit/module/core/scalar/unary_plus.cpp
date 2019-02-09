//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019  Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/unary_plus.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check unary_plus return type")
{
  TTS_EXPR_IS(eve::unary_plus(0.f), float);
  TTS_EXPR_IS(eve::unary_plus(0.), double);

  TTS_EXPR_IS(eve::unary_plus(std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::unary_plus(std::int16_t()), std::int16_t);
  TTS_EXPR_IS(eve::unary_plus(std::int32_t()), std::int32_t);
  TTS_EXPR_IS(eve::unary_plus(std::int64_t()), std::int64_t);

  TTS_EXPR_IS(eve::unary_plus(std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::unary_plus(std::uint16_t()), std::uint16_t);
  TTS_EXPR_IS(eve::unary_plus(std::uint32_t()), std::uint32_t);
  TTS_EXPR_IS(eve::unary_plus(std::uint64_t()), std::uint64_t);
}

TTS_CASE("Check unary_plus behavior")
{
  TTS_EQUAL(eve::unary_plus(std::uint8_t(2)), std::uint8_t(2));
  TTS_EQUAL(eve::unary_plus(std::uint16_t(2)), std::uint16_t(2));
  TTS_EQUAL(eve::unary_plus(std::int8_t(2)), std::int8_t(2));
  TTS_EQUAL(eve::unary_plus(std::int16_t(2)), std::int16_t(2));

  TTS_EQUAL(eve::unary_plus(-1.5f), -1.5f);
  TTS_EQUAL(eve::unary_plus(-4.753), -4.753);
}
