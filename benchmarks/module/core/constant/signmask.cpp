//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/constant/mzero.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check signmask return type")
{
  TTS_EXPR_IS(eve::Signmask<float>(), float);
  TTS_EXPR_IS(eve::Signmask<double>(), double);

  TTS_EXPR_IS(eve::Signmask<std::int8_t>(), std::int8_t);
  TTS_EXPR_IS(eve::Signmask<std::int16_t>(), std::int16_t);
  TTS_EXPR_IS(eve::Signmask<std::int32_t>(), std::int32_t);
  TTS_EXPR_IS(eve::Signmask<std::int64_t>(), std::int64_t);

  TTS_EXPR_IS(eve::Signmask<std::uint8_t>(), std::uint8_t);
  TTS_EXPR_IS(eve::Signmask<std::uint16_t>(), std::uint16_t);
  TTS_EXPR_IS(eve::Signmask<std::uint32_t>(), std::uint32_t);
  TTS_EXPR_IS(eve::Signmask<std::uint64_t>(), std::uint64_t);
}

TTS_CASE("Check signmask behavior")
{
  TTS_EQUAL(eve::Signmask<std::uint8_t>(), std::uint8_t(0x80U));
  TTS_EQUAL(eve::Signmask<std::uint16_t>(), std::uint16_t(0x8000U));
  TTS_EQUAL(eve::Signmask<std::uint32_t>(), std::uint32_t(0x80000000U));
  TTS_EQUAL(eve::Signmask<std::uint64_t>(), std::uint64_t(0x8000000000000000ULL));
  TTS_EQUAL(eve::Signmask<std::int8_t>(), std::int8_t(-128));
  TTS_EQUAL(eve::Signmask<std::int16_t>(), std::int16_t(-32768));
  TTS_EQUAL(eve::Signmask<std::int32_t>(), std::int32_t(-2147483647 - 1));
  TTS_EQUAL(eve::Signmask<std::int64_t>(), std::int64_t(-9223372036854775807LL - 1));

  TTS_EQUAL(eve::Signmask<double>(), eve::Mzero<double>());
  TTS_EQUAL(eve::Signmask<float>(), eve::Mzero<float>());
}
