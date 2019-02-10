//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019  Jean-Thierry Lapresté

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/constant/minf.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>
#include <limits>

TTS_CASE("Check minf return type")
{
  TTS_EXPR_IS(eve::Minf<float>(), float);
  TTS_EXPR_IS(eve::Minf<double>(), double);

  TTS_EXPR_IS(eve::Minf<std::int8_t>(), std::int8_t);
  TTS_EXPR_IS(eve::Minf<std::int16_t>(), std::int16_t);
  TTS_EXPR_IS(eve::Minf<std::int32_t>(), std::int32_t);
  TTS_EXPR_IS(eve::Minf<std::int64_t>(), std::int64_t);

  TTS_EXPR_IS(eve::Minf<std::uint8_t>(), std::uint8_t);
  TTS_EXPR_IS(eve::Minf<std::uint16_t>(), std::uint16_t);
  TTS_EXPR_IS(eve::Minf<std::uint32_t>(), std::uint32_t);
  TTS_EXPR_IS(eve::Minf<std::uint64_t>(), std::uint64_t);
}

TTS_CASE("Check minf behavior")
{
  TTS_EQUAL(eve::Minf<std::uint8_t>(), std::uint8_t(0));
  TTS_EQUAL(eve::Minf<std::uint16_t>(), std::uint16_t(0));
  TTS_EQUAL(eve::Minf<std::int8_t>(), std::int8_t(-128));
  TTS_EQUAL(eve::Minf<std::int16_t>(), std::int16_t(-32768));

  TTS_EQUAL(eve::Minf<double>(), -std::numeric_limits<double>::infinity());
  TTS_EQUAL(eve::Minf<float>(), -std::numeric_limits<float>::infinity());
}
