//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/is_gez.hpp>
#include <eve/logical.hpp>
#include <eve/as_logical.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check is_gez return type")
{
  TTS_EXPR_IS(eve::is_gez(0.f),  eve::as_logical_t<float>);
  TTS_EXPR_IS(eve::is_gez(0.),  eve::as_logical_t<double>);

  TTS_EXPR_IS(eve::is_gez(std::int8_t()), eve::as_logical_t<std::int8_t>);
  TTS_EXPR_IS(eve::is_gez(std::int16_t()), eve::as_logical_t<std::int16_t>);
  TTS_EXPR_IS(eve::is_gez(std::int32_t()), eve::as_logical_t<std::int32_t>);
  TTS_EXPR_IS(eve::is_gez(std::int64_t()), eve::as_logical_t<std::int64_t>);

  TTS_EXPR_IS(eve::is_gez(std::uint8_t()), eve::as_logical_t<std::uint8_t>);
  TTS_EXPR_IS(eve::is_gez(std::uint16_t()), eve::as_logical_t<std::uint16_t>);
  TTS_EXPR_IS(eve::is_gez(std::uint32_t()), eve::as_logical_t<std::uint32_t>);
  TTS_EXPR_IS(eve::is_gez(std::uint64_t()), eve::as_logical_t<std::uint64_t>);
}

TTS_CASE("Check is_gez behavior")
{

  TTS_EQUAL(eve::is_gez(std::uint8_t(1)), eve::True<eve::logical<std::uint8_t>>());
  TTS_EQUAL(eve::is_gez(std::uint16_t(1)), eve::True<eve::logical<std::uint16_t>>());
  TTS_EQUAL(eve::is_gez(std::uint32_t(1)), eve::True<eve::logical<std::uint32_t>>());
  TTS_EQUAL(eve::is_gez(std::uint64_t(1)), eve::True<eve::logical<std::uint64_t>>());
  TTS_EQUAL(eve::is_gez(std::int8_t(1)), eve::True<eve::logical<std::int8_t>>());
  TTS_EQUAL(eve::is_gez(std::int16_t(1)), eve::True<eve::logical<std::int16_t>>());
  TTS_EQUAL(eve::is_gez(std::int32_t(1)), eve::True<eve::logical<std::int32_t>>());
  TTS_EQUAL(eve::is_gez(std::int64_t(1)), eve::True<eve::logical<std::int64_t>>());
  
  TTS_EQUAL(eve::is_gez(std::uint8_t(0)), eve::True<eve::logical<std::uint8_t>>());
  TTS_EQUAL(eve::is_gez(std::uint16_t(0)), eve::True<eve::logical<std::uint16_t>>());
  TTS_EQUAL(eve::is_gez(std::uint32_t(0)), eve::True<eve::logical<std::uint32_t>>());
  TTS_EQUAL(eve::is_gez(std::uint64_t(0)), eve::True<eve::logical<std::uint64_t>>());
  TTS_EQUAL(eve::is_gez(std::int8_t(0)), eve::True<eve::logical<std::int8_t>>());
  TTS_EQUAL(eve::is_gez(std::int16_t(0)), eve::True<eve::logical<std::int16_t>>());
  TTS_EQUAL(eve::is_gez(std::int32_t(0)), eve::True<eve::logical<std::int32_t>>());
  TTS_EQUAL(eve::is_gez(std::int64_t(0)), eve::True<eve::logical<std::int64_t>>());

  TTS_EQUAL(eve::is_gez(std::int8_t(-1)), eve::False<eve::logical<std::int8_t>>());
  TTS_EQUAL(eve::is_gez(std::int16_t(-1)), eve::False<eve::logical<std::int16_t>>());
  TTS_EQUAL(eve::is_gez(std::int32_t(-1)), eve::False<eve::logical<std::int32_t>>());
  TTS_EQUAL(eve::is_gez(std::int64_t(-1)), eve::False<eve::logical<std::int64_t>>());


  TTS_EQUAL(eve::is_gez(-1.5f), eve::False<eve::logical<float>>());
  TTS_EQUAL(eve::is_gez(-4.753),eve::False<eve::logical<double>>());
  TTS_EQUAL(eve::is_gez(-0.0f), eve::True<eve::logical<float>>());
  TTS_EQUAL(eve::is_gez(0.0),eve::True<eve::logical<double>>());
}
