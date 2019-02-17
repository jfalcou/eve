//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/extract.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check extract return type")
{
  TTS_EXPR_IS(eve::extract(0.f,1), float);
  TTS_EXPR_IS(eve::extract(0., 0), double);
  TTS_EXPR_IS(eve::extract(0.f, std::int32_t()), float);
  TTS_EXPR_IS(eve::extract(0., std::int64_t()), double);
  TTS_EXPR_IS(eve::extract(std::int32_t(), 0), std::int32_t);
  TTS_EXPR_IS(eve::extract(std::int64_t(), 1), std::int64_t);

  TTS_EXPR_IS(eve::extract(std::int8_t(), std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::extract(std::int16_t(), std::int8_t()), std::int16_t);
  TTS_EXPR_IS(eve::extract(std::int32_t(), std::int8_t()), std::int32_t);
  TTS_EXPR_IS(eve::extract(std::int64_t(), std::int8_t()), std::int64_t);

  TTS_EXPR_IS(eve::extract(std::uint8_t(), std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::extract(std::uint16_t(), std::uint8_t()), std::uint16_t);
  TTS_EXPR_IS(eve::extract(std::uint32_t(), std::uint8_t()), std::uint32_t);
  TTS_EXPR_IS(eve::extract(std::uint64_t(), std::uint8_t()), std::uint64_t);
}

TTS_CASE("Check extract behavior")
{
  TTS_EQUAL(eve::extract(std::uint8_t(23), 1), std::uint8_t(23));
  TTS_EQUAL(eve::extract(std::uint16_t(1000), 0), std::uint16_t(1000));
  TTS_EQUAL(eve::extract(std::uint32_t(23), 1), std::uint32_t(23));
  TTS_EQUAL(eve::extract(std::uint64_t(1000), 0), std::uint64_t(1000));
  TTS_EQUAL(eve::extract(std::int8_t(23), 1), std::int8_t(23));
  TTS_EQUAL(eve::extract(std::int16_t(1000), 0), std::int16_t(1000));
  TTS_EQUAL(eve::extract(std::int32_t(23), 1), std::int32_t(23));
  TTS_EQUAL(eve::extract(std::int64_t(1000), 0), std::int64_t(1000));

  TTS_EQUAL(eve::extract(-1.5f, 1), -1.5f);
  TTS_EQUAL(eve::extract(-4.753, 1), -4.753);
}
