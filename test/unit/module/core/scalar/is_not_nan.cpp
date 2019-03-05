//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//================================================================================================== 

#include <eve/function/scalar/is_not_nan.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check is_not_nan return type")
{
  TTS_EXPR_IS(eve::is_not_nan(0.f),  eve::logical<float>);
  TTS_EXPR_IS(eve::is_not_nan(0.),  eve::logical< double>);

  TTS_EXPR_IS(eve::is_not_nan(std::int8_t() ),     eve::logical< std::int8_t>);
  TTS_EXPR_IS(eve::is_not_nan(std::int16_t()),   eve::logical< std::int16_t>);
  TTS_EXPR_IS(eve::is_not_nan(std::int32_t()),   eve::logical< std::int32_t>);
  TTS_EXPR_IS(eve::is_not_nan(std::int64_t()),   eve::logical< std::int64_t>);

  TTS_EXPR_IS(eve::is_not_nan(std::uint8_t() ),   eve::logical< std::uint8_t>);
  TTS_EXPR_IS(eve::is_not_nan(std::uint16_t()), eve::logical< std::uint16_t>);
  TTS_EXPR_IS(eve::is_not_nan(std::uint32_t()), eve::logical< std::uint32_t>);
  TTS_EXPR_IS(eve::is_not_nan(std::uint64_t()), eve::logical< std::uint64_t>);
}

TTS_CASE("Check is_not_nan behavior")
{
  TTS_EQUAL(eve::is_not_nan(std::uint8_t(1) ), true);
  TTS_EQUAL(eve::is_not_nan(std::uint16_t(1)), true);
  TTS_EQUAL(eve::is_not_nan(std::uint32_t(1)), true);
  TTS_EQUAL(eve::is_not_nan(std::uint64_t(1)), true);
  TTS_EQUAL(eve::is_not_nan(std::int8_t(1)), true);
  TTS_EQUAL(eve::is_not_nan(std::int16_t(1) ), true);
  TTS_EQUAL(eve::is_not_nan(std::int32_t(1) ), true);
  TTS_EQUAL(eve::is_not_nan(std::int64_t(1) ), true);
  TTS_EQUAL(eve::is_not_nan(1.5f), true);
  TTS_EQUAL(eve::is_not_nan(4.75), true);

  TTS_EQUAL(eve::is_not_nan(0.0f/0.0f), false);
  TTS_EQUAL(eve::is_not_nan(-0.0/0.0), false);
}







