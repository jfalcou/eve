//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DIV_HPP
#define DIV_HPP

#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/function/div.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE( "Check div return type" )
{
  TTS_EXPR_IS(eve::div[Type()]( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::div[eve::logical<Type>()]( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::div[true]( Type(), Type() ) , Type );
}

TTS_CASE("Check conditional div behavior")
{
  Type tv{25};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL ( eve::div[ 1    ](tv, fv), tv/fv);
  TTS_EQUAL ( eve::div[ 1.0  ](tv, fv), tv/fv);
  TTS_EQUAL ( eve::div[ true ](tv, fv), tv/fv);
  TTS_EQUAL ( eve::div[ t    ](tv, fv), tv/fv);
  TTS_EQUAL ( eve::div[ 0    ](tv, fv), tv);
  TTS_EQUAL ( eve::div[ 0.0  ](tv, fv), tv);
  TTS_EQUAL ( eve::div[ false](tv, fv), tv);
  TTS_EQUAL ( eve::div[ f    ](tv, fv), tv);
}

#endif
