//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/bitwise_mask.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check bitwise_mask return type")
{
  TTS_EXPR_IS(eve::bitwise_mask(0.f), float);
  TTS_EXPR_IS(eve::bitwise_mask(0.), double);

  TTS_EXPR_IS(eve::bitwise_mask(std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::bitwise_mask(std::int16_t()), std::int16_t);
  TTS_EXPR_IS(eve::bitwise_mask(std::int32_t()), std::int32_t);
  TTS_EXPR_IS(eve::bitwise_mask(std::int64_t()), std::int64_t);

  TTS_EXPR_IS(eve::bitwise_mask(std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::bitwise_mask(std::uint16_t()), std::uint16_t);
  TTS_EXPR_IS(eve::bitwise_mask(std::uint32_t()), std::uint32_t);
  TTS_EXPR_IS(eve::bitwise_mask(std::uint64_t()), std::uint64_t);
}

TTS_CASE("Check bitwise_mask behavior")
{
  TTS_EQUAL(eve::bitwise_mask(std::uint8_t(2)),  eve::Allbits<std::uint8_t>());
  TTS_EQUAL(eve::bitwise_mask(std::uint16_t(2)), eve::Allbits<std::uint16_t>());
  TTS_EQUAL(eve::bitwise_mask(std::uint32_t(2)), eve::Allbits<std::uint32_t>());
  TTS_EQUAL(eve::bitwise_mask(std::uint64_t(2)), eve::Allbits<std::uint64_t>());
  TTS_EQUAL(eve::bitwise_mask(std::int8_t(2)),   eve::Allbits<std::int8_t>());
  TTS_EQUAL(eve::bitwise_mask(std::int16_t(2)),  eve::Allbits<std::int16_t>());
  TTS_EQUAL(eve::bitwise_mask(std::int32_t(2)),  eve::Allbits<std::int32_t>());
  TTS_EQUAL(eve::bitwise_mask(std::int64_t(2)),  eve::Allbits<std::int64_t>());

  TTS_EQUAL(eve::bitwise_mask(std::uint8_t(0)),  eve::Zero<std::uint8_t>());
  TTS_EQUAL(eve::bitwise_mask(std::uint16_t(0)), eve::Zero<std::uint16_t>());
  TTS_EQUAL(eve::bitwise_mask(std::uint32_t(0)), eve::Zero<std::uint32_t>());
  TTS_EQUAL(eve::bitwise_mask(std::uint64_t(0)), eve::Zero<std::uint64_t>());
  TTS_EQUAL(eve::bitwise_mask(std::int8_t(0)),   eve::Zero<std::int8_t>());
  TTS_EQUAL(eve::bitwise_mask(std::int16_t(0)),  eve::Zero<std::int16_t>());
  TTS_EQUAL(eve::bitwise_mask(std::int32_t(0)),  eve::Zero<std::int32_t>());
  TTS_EQUAL(eve::bitwise_mask(std::int64_t(0)),  eve::Zero<std::int64_t>());


  TTS_IEEE_EQUAL(eve::bitwise_mask(-1.5f), eve::Allbits<float>());
  TTS_IEEE_EQUAL(eve::bitwise_mask(-4.753),eve::Allbits<double>());
  TTS_EQUAL(eve::bitwise_mask(0.0f), eve::Zero<float>());
  TTS_EQUAL(eve::bitwise_mask(0.0),eve::Zero<double>());
  TTS_EQUAL(eve::bitwise_mask(-0.0f), eve::Zero<float>());
  TTS_EQUAL(eve::bitwise_mask(-0.0),eve::Zero<double>());
}
