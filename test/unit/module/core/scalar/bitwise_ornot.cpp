//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/bitwise_ornot.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE( "Check bitwise_ornot return type" )
{
  TTS_EXPR_IS(eve::bitwise_ornot(0.f, 0.f       ) , float  );
  TTS_EXPR_IS(eve::bitwise_ornot(0. , 0.        ) , double );
  TTS_EXPR_IS(eve::bitwise_ornot(0.f, std::int32_t() ) , float  );
  TTS_EXPR_IS(eve::bitwise_ornot(0. , std::int64_t() ) , double );
  TTS_EXPR_IS(eve::bitwise_ornot(std::int32_t(), 0.f ) , std::int32_t  );
  TTS_EXPR_IS(eve::bitwise_ornot(std::int64_t(), 0.  ) , std::int64_t );

  TTS_EXPR_IS(eve::bitwise_ornot(std::int8_t() , std::int8_t()  ) , std::int8_t  );
  TTS_EXPR_IS(eve::bitwise_ornot(std::int16_t(), std::int16_t() ) , std::int16_t );
  TTS_EXPR_IS(eve::bitwise_ornot(std::int32_t(), std::int32_t() ) , std::int32_t );
  TTS_EXPR_IS(eve::bitwise_ornot(std::int64_t(), std::int64_t() ) , std::int64_t );

  TTS_EXPR_IS(eve::bitwise_ornot(std::uint8_t() , std::uint8_t()  ) , std::uint8_t  );
  TTS_EXPR_IS(eve::bitwise_ornot(std::uint16_t(), std::uint16_t() ) , std::uint16_t );
  TTS_EXPR_IS(eve::bitwise_ornot(std::uint32_t(), std::uint32_t() ) , std::uint32_t );
  TTS_EXPR_IS(eve::bitwise_ornot(std::uint64_t(), std::uint64_t() ) , std::uint64_t );
}

TTS_CASE( "Check bitwise_ornot behavior" )
{
  TTS_EQUAL ( eve::bitwise_ornot( std::uint8_t(0b01000011)
                                 , std::uint8_t(0b01011010)
                                 )
            , std::uint8_t(std::uint8_t(0b01000011) | ~std::uint8_t(0b01011010))
            );
  TTS_EQUAL ( eve::bitwise_ornot( std::uint16_t(0b1100001101000011)
                                 , std::uint16_t(0b0111010101011010)
                                 )
            , std::uint16_t( std::uint16_t(0b1100001101000011) | ~std::uint16_t(0b0111010101011010))
            );

  TTS_EQUAL ( eve::bitwise_ornot( -1.5f  , ~0x0U  ) ,  -1.5f  );
  TTS_EQUAL ( eve::bitwise_ornot( -4.753 , ~0x0ULL) ,  -4.753 );
}
