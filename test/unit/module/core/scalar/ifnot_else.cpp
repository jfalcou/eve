//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU 
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/ifnot_else.hpp>
#include <eve/logical.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE( "Check ifnot_else return type" )
{
  TTS_EXPR_IS(eve::ifnot_else(std::uint32_t(), float(), float() ) , float );
  TTS_EXPR_IS(eve::ifnot_else(std::uint64_t(), double(), double() ) , double );

  TTS_EXPR_IS(eve::ifnot_else(std::uint8_t() , std::int8_t() , std::int8_t()  ) , std::int8_t  );
  TTS_EXPR_IS(eve::ifnot_else(std::uint16_t(), std::int16_t(), std::int16_t() ) , std::int16_t );
  TTS_EXPR_IS(eve::ifnot_else(std::uint32_t(), std::int32_t(), std::int32_t() ) , std::int32_t );
  TTS_EXPR_IS(eve::ifnot_else(std::uint64_t(), std::int64_t(), std::int64_t() ) , std::int64_t );

  TTS_EXPR_IS(eve::ifnot_else(std::uint8_t() , std::uint8_t() , std::uint8_t()  ) , std::uint8_t  );
  TTS_EXPR_IS(eve::ifnot_else(std::uint16_t(), std::uint16_t(), std::uint16_t() ) , std::uint16_t );
  TTS_EXPR_IS(eve::ifnot_else(std::uint32_t(), std::uint32_t(), std::uint32_t() ) , std::uint32_t );
  TTS_EXPR_IS(eve::ifnot_else(std::uint64_t(), std::uint64_t(), std::uint64_t() ) , std::uint64_t );
}

TTS_CASE( "Check ifnot_else behavior" )
{
  TTS_EQUAL ( eve::ifnot_else( 1, 2, 3), 3); 
  TTS_EQUAL ( eve::ifnot_else( 1.0, 2, 3), 3); 
  TTS_EQUAL ( eve::ifnot_else( true, 2, 3), 3);
  TTS_EQUAL ( eve::ifnot_else( eve::True<eve::logical<float>>(), 2, 3), 3);
  TTS_EQUAL ( eve::ifnot_else( 0, 2, 3), 2); 
  TTS_EQUAL ( eve::ifnot_else( 0.0, 2, 3), 2); 
  TTS_EQUAL ( eve::ifnot_else( false, 2, 3), 2); 
  TTS_EQUAL ( eve::ifnot_else( eve::False<eve::logical<float>>(), 2, 3), 2);
}
