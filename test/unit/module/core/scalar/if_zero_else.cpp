//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU 
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include <eve/function/if_else.hpp>
#include <eve/logical.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/zero.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE( "Check if_zero_else return type" )
{
  auto z = eve::zero_; 
  TTS_EXPR_IS(eve::if_else(std::uint32_t(), z, float() ) , float );
  TTS_EXPR_IS(eve::if_else(std::uint64_t(), z, double() ) , double );
  
  TTS_EXPR_IS(eve::if_else(std::uint8_t(),  z, std::int8_t() ) , std::int8_t  );
  TTS_EXPR_IS(eve::if_else(std::uint16_t(), z, std::int16_t()) , std::int16_t );
  TTS_EXPR_IS(eve::if_else(std::uint32_t(), z, std::int32_t()) , std::int32_t );
  TTS_EXPR_IS(eve::if_else(std::uint64_t(), z, std::int64_t()) , std::int64_t );
  
  TTS_EXPR_IS(eve::if_else(std::uint8_t() , z, std::uint8_t()  ) , std::uint8_t  );
  TTS_EXPR_IS(eve::if_else(std::uint16_t(), z, std::uint16_t() ) , std::uint16_t );
  TTS_EXPR_IS(eve::if_else(std::uint32_t(), z, std::uint32_t() ) , std::uint32_t );
  TTS_EXPR_IS(eve::if_else(std::uint64_t(), z, std::uint64_t() ) , std::uint64_t );
}

TTS_CASE( "Check if_zero_else behavior" )
{
  auto z = eve::zero_; 
  TTS_EQUAL ( eve::if_else( 0, z, 2), 2); 
  TTS_EQUAL ( eve::if_else( 0.0, z, 2), 2); 
  TTS_EQUAL ( eve::if_else( false, z, 2), 2);
  TTS_EQUAL ( eve::if_else( eve::False<eve::logical<float>>(), z, 2), 2);
  TTS_EQUAL ( eve::if_else( 1, z, 2), 0); 
  TTS_EQUAL ( eve::if_else( 1.0, z, 2),  0); 
  TTS_EQUAL ( eve::if_else( true, z, 2),  0); 
  TTS_EQUAL ( eve::if_else( eve::True<eve::logical<float>>(), z, 2), 0);
}
