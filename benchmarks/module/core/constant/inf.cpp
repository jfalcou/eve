//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <eve/module/core/constant/inf.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check inf return type")
{
  TTS_EXPR_IS(eve::Inf<float>(), float);
  TTS_EXPR_IS(eve::Inf<double>(), double);

  TTS_EXPR_IS(eve::Inf<std::int8_t>(), std::int8_t);
  TTS_EXPR_IS(eve::Inf<std::int16_t>(), std::int16_t);
  TTS_EXPR_IS(eve::Inf<std::int32_t>(), std::int32_t);
  TTS_EXPR_IS(eve::Inf<std::int64_t>(), std::int64_t);

  TTS_EXPR_IS(eve::Inf<std::uint8_t>(), std::uint8_t);
  TTS_EXPR_IS(eve::Inf<std::uint16_t>(), std::uint16_t);
  TTS_EXPR_IS(eve::Inf<std::uint32_t>(), std::uint32_t);
  TTS_EXPR_IS(eve::Inf<std::uint64_t>(), std::uint64_t);
}

TTS_CASE("Check inf behavior")
{
  TTS_EQUAL(eve::Inf<std::uint8_t>(), std::uint8_t(0xFF));
  TTS_EQUAL(eve::Inf<std::uint16_t>(), std::uint16_t(0xFFFF));
  TTS_EQUAL(eve::Inf<std::uint32_t>(), std::uint32_t(0xFFFFFFFFUL));
  TTS_EQUAL(eve::Inf<std::uint64_t>(), std::uint64_t(0xFFFFFFFFFFFFFFFFULL));
  TTS_EQUAL(eve::Inf<std::int8_t>(), std::int8_t(0x7F));
  TTS_EQUAL(eve::Inf<std::int16_t>(), std::int16_t(0x7FFF));
  TTS_EQUAL(eve::Inf<std::int32_t>(), std::int32_t(0x7FFFFFFFUL));
  TTS_EQUAL(eve::Inf<std::int64_t>(), std::int64_t(0x7FFFFFFFFFFFFFFFULL));

  TTS_EQUAL(eve::Inf<double>(), std::numeric_limits<double>::infinity());
  TTS_EQUAL(eve::Inf<float>(), std::numeric_limits<float>::infinity());
}
