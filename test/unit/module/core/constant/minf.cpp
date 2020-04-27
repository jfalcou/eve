//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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

TTS_CASE_TPL("Check minf return type", EVE_TYPE)
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

TTS_CASE_TPL("Check minf behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::Minf<std::uint8_t>(), std::uint8_t(0));
  TTS_EQUAL(eve::Minf<std::uint16_t>(), std::uint16_t(0));
  TTS_EQUAL(eve::Minf<std::uint32_t>(), std::uint32_t(0));
  TTS_EQUAL(eve::Minf<std::uint64_t>(), std::uint64_t(0));
  TTS_EQUAL(eve::Minf<std::int8_t>(), std::int8_t(0x80));
  TTS_EQUAL(eve::Minf<std::int16_t>(), std::int16_t(0x8000));
  TTS_EQUAL(eve::Minf<std::int32_t>(), std::int32_t(0x80000000UL));
  TTS_EQUAL(eve::Minf<std::int64_t>(), std::int64_t(0x8000000000000000ULL));

  TTS_EQUAL(eve::Minf<double>(), -std::numeric_limits<double>::infinity());
  TTS_EQUAL(eve::Minf<float>(), -std::numeric_limits<float>::infinity());
}
