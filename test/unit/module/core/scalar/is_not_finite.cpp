//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//================================================================================================== 

#include <eve/function/scalar/is_not_finite.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check is_not_finite return type")
{
  TTS_EXPR_IS(eve::is_not_finite(0.f),  eve::logical<float>);
  TTS_EXPR_IS(eve::is_not_finite(0.),  eve::logical< double>);

  TTS_EXPR_IS(eve::is_not_finite(std::int8_t() ),     eve::logical< std::int8_t>);
  TTS_EXPR_IS(eve::is_not_finite(std::int16_t()),   eve::logical< std::int16_t>);
  TTS_EXPR_IS(eve::is_not_finite(std::int32_t()),   eve::logical< std::int32_t>);
  TTS_EXPR_IS(eve::is_not_finite(std::int64_t()),   eve::logical< std::int64_t>);

  TTS_EXPR_IS(eve::is_not_finite(std::uint8_t() ),   eve::logical< std::uint8_t>);
  TTS_EXPR_IS(eve::is_not_finite(std::uint16_t()), eve::logical< std::uint16_t>);
  TTS_EXPR_IS(eve::is_not_finite(std::uint32_t()), eve::logical< std::uint32_t>);
  TTS_EXPR_IS(eve::is_not_finite(std::uint64_t()), eve::logical< std::uint64_t>);
}

TTS_CASE("Check is_not_finite behavior")
{
  TTS_EQUAL(eve::is_not_finite(std::uint8_t(1) ), false);
  TTS_EQUAL(eve::is_not_finite(std::uint16_t(1)), false);
  TTS_EQUAL(eve::is_not_finite(std::uint32_t(1)), false);
  TTS_EQUAL(eve::is_not_finite(std::uint64_t(1)), false);
  TTS_EQUAL(eve::is_not_finite(std::int8_t(1)), false);
  TTS_EQUAL(eve::is_not_finite(std::int16_t(1) ), false);
  TTS_EQUAL(eve::is_not_finite(std::int32_t(1) ), false);
  TTS_EQUAL(eve::is_not_finite(std::int64_t(1) ), false);
  TTS_EQUAL(eve::is_not_finite(1.5f), false);
  TTS_EQUAL(eve::is_not_finite(4.75), false);

  TTS_EQUAL(eve::is_not_finite(0.0f/0.0f), true);
  TTS_EQUAL(eve::is_not_finite(-0.0/0.0), true);
  TTS_EQUAL(eve::is_not_finite(1.0f/0.0f), true);
  TTS_EQUAL(eve::is_not_finite(-1.0/0.0), true);
}







