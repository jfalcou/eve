//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check nan return type")
{
  TTS_EXPR_IS(eve::Nan<float>(), float);
  TTS_EXPR_IS(eve::Nan<double>(), double);

  TTS_EXPR_IS(eve::Nan<std::int8_t>(), std::int8_t);
  TTS_EXPR_IS(eve::Nan<std::int16_t>(), std::int16_t);
  TTS_EXPR_IS(eve::Nan<std::int32_t>(), std::int32_t);
  TTS_EXPR_IS(eve::Nan<std::int64_t>(), std::int64_t);

  TTS_EXPR_IS(eve::Nan<std::uint8_t>(), std::uint8_t);
  TTS_EXPR_IS(eve::Nan<std::uint16_t>(), std::uint16_t);
  TTS_EXPR_IS(eve::Nan<std::uint32_t>(), std::uint32_t);
  TTS_EXPR_IS(eve::Nan<std::uint64_t>(), std::uint64_t);
}

TTS_CASE("Check nan behavior")
{
  TTS_EQUAL(eve::Nan<std::uint8_t>(), std::uint8_t(0));
  TTS_EQUAL(eve::Nan<std::uint16_t>(), std::uint16_t(0));
  TTS_EQUAL(eve::Nan<std::uint32_t>(), std::uint32_t(0));
  TTS_EQUAL(eve::Nan<std::uint64_t>(), std::uint64_t(0));
  TTS_EQUAL(eve::Nan<std::int8_t>(), std::int8_t(0));
  TTS_EQUAL(eve::Nan<std::int16_t>(), std::int16_t(0));
  TTS_EQUAL(eve::Nan<std::int32_t>(), std::int32_t(0));
  TTS_EQUAL(eve::Nan<std::int64_t>(), std::int64_t(0));

  TTS_IEEE_EQUAL(eve::Nan<double>(), eve::Inf<double>() - eve::Inf<double>());
  TTS_IEEE_EQUAL(eve::Nan<float>(), eve::Inf<float>() - eve::Inf<float>());
}
