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
#include <eve/constant/nan.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>

TTS_CASE( "Check if_else_nanrn type" )
{
  auto z = eve::nan_; 
  TTS_EXPR_IS(eve::if_else(std::uint32_t(), z, float() ) , float );
  TTS_EXPR_IS(eve::if_else(std::uint64_t(), z, double() ) , double );
}

TTS_CASE( "Check if_else_nanvior" )
{
  auto z = eve::nan_; 
  TTS_IEEE_EQUAL ( eve::if_else( 0, z, 2.0), 2.0); 
  TTS_IEEE_EQUAL ( eve::if_else( 0.0, z, 2.0), 2.0); 
  TTS_IEEE_EQUAL ( eve::if_else( false, z, 2.0), 2.0);
  TTS_IEEE_EQUAL ( eve::if_else( eve::False<eve::logical<float>>(), z, 2.0f), 2.0f);
  TTS_IEEE_EQUAL ( eve::if_else( 1, z, 2.0), eve::Nan<double>()); 
  TTS_IEEE_EQUAL ( eve::if_else( 1.0, z, 2.0),  eve::Nan<double>()); 
  TTS_IEEE_EQUAL ( eve::if_else( true, z, 2.0),  eve::Nan<double>()); 
  TTS_IEEE_EQUAL ( eve::if_else( eve::True<eve::logical<float>>(), z, 2.0), eve::Nan<double>());
}
