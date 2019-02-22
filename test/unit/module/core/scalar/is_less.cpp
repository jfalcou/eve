//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/is_less.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check is_less return type")
{
  TTS_EXPR_IS(eve::is_less(0.f, 0.f),  eve::logical<float>);
  TTS_EXPR_IS(eve::is_less(0., 0.),  eve::logical< double>);

  TTS_EXPR_IS(eve::is_less(std::int8_t(), std::int8_t()),     eve::logical< std::int8_t>);
  TTS_EXPR_IS(eve::is_less(std::int16_t(), std::int16_t()),   eve::logical< std::int16_t>);
  TTS_EXPR_IS(eve::is_less(std::int32_t(), std::int32_t()),   eve::logical< std::int32_t>);
  TTS_EXPR_IS(eve::is_less(std::int64_t(), std::int64_t()),   eve::logical< std::int64_t>);

  TTS_EXPR_IS(eve::is_less(std::uint8_t(), std::uint8_t()),   eve::logical< std::uint8_t>);
  TTS_EXPR_IS(eve::is_less(std::uint16_t(), std::uint16_t()), eve::logical< std::uint16_t>);
  TTS_EXPR_IS(eve::is_less(std::uint32_t(), std::uint32_t()), eve::logical< std::uint32_t>);
  TTS_EXPR_IS(eve::is_less(std::uint64_t(), std::uint64_t()), eve::logical< std::uint64_t>);
}

TTS_CASE("Check is_less behavior")
{
  TTS_EQUAL(eve::is_less(std::uint8_t(1), std::uint8_t(2)), true);
  TTS_EQUAL(eve::is_less(std::uint16_t(1), std::uint16_t(2)), true);
  TTS_EQUAL(eve::is_less(std::uint32_t(1), std::uint32_t(2)), true);
  TTS_EQUAL(eve::is_less(std::uint64_t(1), std::uint64_t(2)), true);
  TTS_EQUAL(eve::is_less(std::int8_t(1), std::int8_t(2)), true);
  TTS_EQUAL(eve::is_less(std::int16_t(1), std::int16_t(2)), true);
  TTS_EQUAL(eve::is_less(std::int32_t(1), std::int32_t(2)), true);
  TTS_EQUAL(eve::is_less(std::int64_t(1), std::int64_t(2)), true);
  TTS_EQUAL(eve::is_less(1.5f, -1.5f), false);
  TTS_EQUAL(eve::is_less(4.753, -4.753), false);

  TTS_EQUAL(eve::is_less(std::uint8_t(3), std::uint8_t(2)), false);
  TTS_EQUAL(eve::is_less(std::uint16_t(3), std::uint16_t(2)), false);
  TTS_EQUAL(eve::is_less(std::uint32_t(3), std::uint32_t(2)), false);
  TTS_EQUAL(eve::is_less(std::uint64_t(3), std::uint64_t(2)), false);
  TTS_EQUAL(eve::is_less(std::int8_t(3), std::int8_t(2)), false);
  TTS_EQUAL(eve::is_less(std::int16_t(3), std::int16_t(2)), false);
  TTS_EQUAL(eve::is_less(std::int32_t(3), std::int32_t(2)), false);
  TTS_EQUAL(eve::is_less(std::int64_t(3), std::int64_t(2)), false);
  TTS_EQUAL(eve::is_less(1.5f, 1.6f), true);
  TTS_EQUAL(eve::is_less(-4.753, 4.753), true);
}







