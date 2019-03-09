//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/abs.hpp>
#include <eve/constant/zero.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp> 
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE("Check abs return type") 
{
  auto z = eve::zero_; 
  std::cout << tts::type_id(z) << std::endl; 
  TTS_EXPR_IS(eve::abs(0.f), float);
  TTS_EXPR_IS(eve::abs(0.), double);

  TTS_EXPR_IS(eve::abs(std::int8_t()), std::int8_t);
  TTS_EXPR_IS(eve::abs(std::int16_t()), std::int16_t);
  TTS_EXPR_IS(eve::abs(std::int32_t()), std::int32_t);
  TTS_EXPR_IS(eve::abs(std::int64_t()), std::int64_t);

  TTS_EXPR_IS(eve::abs(std::uint8_t()), std::uint8_t);
  TTS_EXPR_IS(eve::abs(std::uint16_t()), std::uint16_t);
  TTS_EXPR_IS(eve::abs(std::uint32_t()), std::uint32_t);
  TTS_EXPR_IS(eve::abs(std::uint64_t()), std::uint64_t);
}

TTS_CASE("Check abs behavior")
{
  TTS_EQUAL(eve::abs(std::uint8_t(2)), std::uint8_t(2));
  TTS_EQUAL(eve::abs(std::uint16_t(2)), std::uint16_t(2));
  TTS_EQUAL(eve::abs(std::uint32_t(2)), std::uint32_t(2));
  TTS_EQUAL(eve::abs(std::uint64_t(2)), std::uint64_t(2));
  
  TTS_EQUAL(eve::abs(std::int8_t(-2)), std::int8_t(2));
  TTS_EQUAL(eve::abs(std::int16_t(-2)), std::int16_t(2));
  TTS_EQUAL(eve::abs(std::int32_t(-2)), std::int32_t(2));
  TTS_EQUAL(eve::abs(std::int64_t(-2)), std::int64_t(2));


  TTS_EQUAL(eve::abs(-1.5f), 1.5f);
  TTS_EQUAL(eve::abs(-4.753), 4.753);
}
