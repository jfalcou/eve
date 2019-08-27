//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ELSE_ZERO_HPP
#define IF_ELSE_ZERO_HPP

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
  TTS_EXPR_IS(eve::if_else(Type(), Type(), eve::zero_ ) , Type );
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>(), Type(), eve::zero_ ) , Type );
  TTS_EXPR_IS(eve::if_else(true  , Type(), eve::zero_ ) , Type );
}

TTS_CASE("Check if_else(., ., zero_) behavior ")
{
  auto f = eve::Zero<Type>();
  auto t = eve::One<Type>();

  TTS_EQUAL ( eve::if_else( 1   , t  , eve::zero_), t);
  TTS_EQUAL ( eve::if_else( 1.0 , t  , eve::zero_), t);
  TTS_EQUAL ( eve::if_else( true, t  , eve::zero_), t);
  TTS_EQUAL ( eve::if_else( eve::True<Type>(), t  , eve::zero_), t);
  TTS_EQUAL ( eve::if_else( t   , t  , eve::zero_), t);
  TTS_EQUAL ( eve::if_else( 0   , t  , eve::zero_), f);
  TTS_EQUAL ( eve::if_else( 0.0 , t  , eve::zero_), f);
  TTS_EQUAL ( eve::if_else( false, t , eve::zero_), f);
  TTS_EQUAL ( eve::if_else( eve::False<Type>(), t  , eve::zero_), f);
  TTS_EQUAL ( eve::if_else( f   , t  , eve::zero_), f);
}

#endif
