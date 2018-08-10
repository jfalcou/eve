//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/bitwise_cast.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check bitwise_cast return type" )
{
  TTS_EXPR_IS(eve::bitwise_cast<int32_t>(float())   , int32_t );
  TTS_EXPR_IS(eve::bitwise_cast<int64_t>(double())  , int64_t );
  TTS_EXPR_IS(eve::bitwise_cast<double> (int64_t()) , double  );
  TTS_EXPR_IS(eve::bitwise_cast<float>  (int32_t()) , float   );
}

// Fake pseudo type for bitwise casting purpose
struct foo
{
  std::uint8_t  bytes[2];
  std::uint16_t word;
};

TTS_CASE( "Check bitwise_cast behavior" )
{
  TTS_EQUAL(eve::bitwise_cast<std::uint32_t>( 1.f ) , 0x3F800000UL);
  TTS_EQUAL(eve::bitwise_cast<float>(0x3F800000)    , 1.f         );

  foo f = eve::bitwise_cast<foo>(0xFFFFFFFFU);
  TTS_EQUAL( f.bytes[0], std::uint8_t(0xFF));
  TTS_EQUAL( f.bytes[1], std::uint8_t(0xFF));
  TTS_EQUAL( f.word    , std::uint16_t(0xFFFF));
}
