//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019  Jean-Thierry Lapresté

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/bitwise_not.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE( "Check bitwise_not return type" )
{
  TTS_EXPR_IS(eve::bitwise_not(0.f       ) , float  );
  TTS_EXPR_IS(eve::bitwise_not(0.        ) , double );

  TTS_EXPR_IS(eve::bitwise_not(std::int8_t()  ) , std::int8_t  );
  TTS_EXPR_IS(eve::bitwise_not(std::int16_t() ) , std::int16_t );
  TTS_EXPR_IS(eve::bitwise_not(std::int32_t() ) , std::int32_t );
  TTS_EXPR_IS(eve::bitwise_not(std::int64_t() ) , std::int64_t );

  TTS_EXPR_IS(eve::bitwise_not(std::uint8_t() ) , std::uint8_t  );
  TTS_EXPR_IS(eve::bitwise_not(std::uint16_t()) , std::uint16_t );
  TTS_EXPR_IS(eve::bitwise_not(std::uint32_t()) , std::uint32_t );
  TTS_EXPR_IS(eve::bitwise_not(std::uint64_t()) , std::uint64_t );
}

TTS_CASE( "Check bitwise_not behavior" )
{
  TTS_EQUAL ( eve::bitwise_not( std::uint8_t(0b01000011) )
            , std::uint8_t(0b10111100)
            );

  TTS_EQUAL ( eve::bitwise_not( std::uint16_t(0b1100001101000011) )
            ,                  std::uint16_t(0b0011110010111100)
            );

  TTS_EQUAL ( eve::bitwise_not( -1.5f ) , 0x1.7ffffep+1  );
  TTS_EQUAL ( eve::bitwise_not( -4.753) , 0x1.cfced916872afp-1 );
}
