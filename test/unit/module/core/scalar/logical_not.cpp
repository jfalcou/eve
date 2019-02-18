//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/logical_not.hpp>
#include <eve/logical.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check logical_not return type")
{
  using eve::logical;
  using eve::True;
  using eve::False; 
  
  TTS_EXPR_IS(eve::logical_not(0.f), logical<float>);
  TTS_EXPR_IS(eve::logical_not(0.), logical<double>);

  TTS_EXPR_IS(eve::logical_not(std::int8_t()),   logical<std::int8_t>);
  TTS_EXPR_IS(eve::logical_not(std::int16_t()),  logical<std::int16_t>);
  TTS_EXPR_IS(eve::logical_not(std::int32_t()),  logical<std::int32_t>);
  TTS_EXPR_IS(eve::logical_not(std::int64_t()),  logical<std::int64_t>);

  TTS_EXPR_IS(eve::logical_not(std::uint8_t()),  logical<std::uint8_t>);
  TTS_EXPR_IS(eve::logical_not(std::uint16_t()), logical<std::uint16_t>);
  TTS_EXPR_IS(eve::logical_not(std::uint32_t()), logical<std::uint32_t>);
  TTS_EXPR_IS(eve::logical_not(std::uint64_t()), logical<std::uint64_t>);
}

TTS_CASE("Check logical_not behavior")
{
  using eve::logical;
  using eve::True;
  using eve::False; 

  TTS_EQUAL(eve::logical_not(std::uint8_t(0)),  True<logical<std::uint8_t>>());
  TTS_EQUAL(eve::logical_not(std::uint16_t(0)), True<logical<std::uint16_t>>());
  TTS_EQUAL(eve::logical_not(std::uint32_t(0)), True<logical<std::uint32_t>>());
  TTS_EQUAL(eve::logical_not(std::uint64_t(0)), True<logical<std::uint64_t>>());
  TTS_EQUAL(eve::logical_not(std::int8_t(0)),   True<logical<std::int8_t>>());
  TTS_EQUAL(eve::logical_not(std::int16_t(0)),  True<logical<std::int16_t>>());
  TTS_EQUAL(eve::logical_not(std::int32_t(0)),  True<logical<std::int32_t>>());
  TTS_EQUAL(eve::logical_not(std::int64_t(0)),  True<logical<std::int64_t>>());
  TTS_EQUAL(eve::logical_not(double(0)),        True<logical<double>>());
  TTS_EQUAL(eve::logical_not(float(0)),         True<logical<float>>());
  TTS_EQUAL(eve::logical_not(-double(0)),       True<logical<double>>());
  TTS_EQUAL(eve::logical_not(-float(0)),        True<logical<float>>());

  TTS_EQUAL(eve::logical_not(std::uint8_t(1)), False<logical<std::uint8_t>>());
  TTS_EQUAL(eve::logical_not(std::uint16_t(1)), False<logical<std::uint16_t>>());
  TTS_EQUAL(eve::logical_not(std::uint32_t(1)), False<logical<std::uint32_t>>());
  TTS_EQUAL(eve::logical_not(std::uint64_t(1)), False<logical<std::uint64_t>>());
  TTS_EQUAL(eve::logical_not(std::int8_t(1)), False<logical<std::int8_t>>());
  TTS_EQUAL(eve::logical_not(std::int16_t(1)), False<logical<std::int16_t>>());
  TTS_EQUAL(eve::logical_not(std::int32_t(1)), False<logical<std::int32_t>>());
  TTS_EQUAL(eve::logical_not(std::int64_t(1)), False<logical<std::int64_t>>());
  TTS_EQUAL(eve::logical_not(double(1)), False<logical<double>>());
  TTS_EQUAL(eve::logical_not(float(1)), False<logical<float>>());


}
