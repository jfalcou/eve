//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ZERO_ELSE_HPP
#define IF_ZERO_ELSE_HPP

#include <eve/function/scalar/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE( "Check if_else return type" )
{
  TTS_EXPR_IS(eve::if_else(Type(), eve::zero_, Type() ) , Type );
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>(), eve::zero_, Type() ) , Type );
  TTS_EXPR_IS(eve::if_else(true , eve::zero_ , Type() ) , Type );
}


TTS_CASE("Check if_else(., zero_, .) behavior ")
{
  auto f = eve::Zero<Type>();
  auto t = eve::One<Type>();

  
  TTS_EQUAL ( eve::if_else( 1   , eve::zero_, t  ), f);
  TTS_EQUAL ( eve::if_else( 1.0 , eve::zero_, t  ), f);
  TTS_EQUAL ( eve::if_else( true, eve::zero_, t  ), f);
  TTS_EQUAL ( eve::if_else( eve::True<Type>()  , eve::zero_, t), f);
  TTS_EQUAL ( eve::if_else( t   , eve::zero_, t  ), f);
  TTS_EQUAL ( eve::if_else( 0   , eve::zero_, t  ), t);
  TTS_EQUAL ( eve::if_else( 0.0 , eve::zero_, t  ), t);
  TTS_EQUAL ( eve::if_else( false , eve::zero_, t), t);
  TTS_EQUAL ( eve::if_else( eve::False<Type>(), eve::zero_, t), t);
  TTS_EQUAL ( eve::if_else( f   , eve::zero_, t), t);
}

#endif
