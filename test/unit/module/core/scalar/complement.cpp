//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019  Jean-Thierry Lapresté

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/scalar/complement.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE( "Check complement return type" )
{
  TTS_EXPR_IS(eve::complement(0.f       ) , float  );
  TTS_EXPR_IS(eve::complement(0.        ) , double );
  TTS_EXPR_IS(eve::complement(0.f ) , float  );
  TTS_EXPR_IS(eve::complement(0.  ) , double );
  TTS_EXPR_IS(eve::complement(std::int32_t() ) , std::int32_t  );
  TTS_EXPR_IS(eve::complement(std::int64_t() ) , std::int64_t );

  TTS_EXPR_IS(eve::complement(std::int8_t()  ) , std::int8_t  );
  TTS_EXPR_IS(eve::complement(std::int16_t() ) , std::int16_t );
  TTS_EXPR_IS(eve::complement(std::int32_t() ) , std::int32_t );
  TTS_EXPR_IS(eve::complement(std::int64_t() ) , std::int64_t );

  TTS_EXPR_IS(eve::complement(std::uint8_t() ) , std::uint8_t  );
  TTS_EXPR_IS(eve::complement(std::uint16_t()) , std::uint16_t );
  TTS_EXPR_IS(eve::complement(std::uint32_t()) , std::uint32_t );
  TTS_EXPR_IS(eve::complement(std::uint64_t()) , std::uint64_t );
}

TTS_CASE( "Check complement behavior" )
{
  TTS_EQUAL ( eve::complement( std::uint8_t(0b01000011) )
            , std::uint8_t(0b10111100)
            );

  TTS_EQUAL ( eve::complement( std::uint16_t(0b1100001101000011) )
            ,                  std::uint16_t(0b0011110010111100) 
            );

  TTS_EQUAL ( eve::complement( -1.5f ) , 0x1.7ffffep+1  );
  TTS_EQUAL ( eve::complement( -4.753) , 0x1.cfced916872afp-1 );
}
