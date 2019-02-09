//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/unary_minus.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check unary_minus return type")
{
  TTS_EXPR_IS(eve::unary_minus(0.f), float);
  TTS_EXPR_IS(eve::unary_minus(0.), double);

  TTS_EXPR_IS(eve::unary_minus(std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::unary_minus(std::int16_t()), std::int16_t);
  TTS_EXPR_IS(eve::unary_minus(std::int32_t()), std::int32_t);
  TTS_EXPR_IS(eve::unary_minus(std::int64_t()), std::int64_t);

  TTS_EXPR_IS(eve::unary_minus(std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::unary_minus(std::uint16_t()), std::uint16_t);
  TTS_EXPR_IS(eve::unary_minus(std::uint32_t()), std::uint32_t);
  TTS_EXPR_IS(eve::unary_minus(std::uint64_t()), std::uint64_t);
}

TTS_CASE("Check unary_minus behavior")
{
  TTS_EQUAL(eve::unary_minus(std::uint8_t(1)), std::uint8_t(-1));
  TTS_EQUAL(eve::unary_minus(std::uint16_t(1)), std::uint16_t(-1));
  TTS_EQUAL(eve::unary_minus(std::int8_t(1)), std::int8_t(-1));
  TTS_EQUAL(eve::unary_minus(std::int16_t(1)), std::int16_t(-1));

  TTS_EQUAL(eve::unary_minus(-1.5f), 1.5f);
  TTS_EQUAL(eve::unary_minus(-4.753), 4.753);
}
