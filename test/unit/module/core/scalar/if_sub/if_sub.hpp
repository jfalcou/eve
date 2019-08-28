//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_SUB_HPP
#define IF_SUB_HPP

#include <eve/function/scalar/add.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp> 
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE( "Check add return type" )
{
  TTS_EXPR_IS(eve::add[Type()]( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::add[eve::logical<Type>()]( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::add[true]( Type(), Type() ) , Type );
}

TTS_CASE("Check conditional add behavior")
{
  Type tv{2};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();    
 
  TTS_EQUAL ( eve::add[ 1    ](tv, fv), tv+fv);
  TTS_EQUAL ( eve::add[ 1.0  ](tv, fv), tv+fv);
  TTS_EQUAL ( eve::add[ true ](tv, fv), tv+fv);
  TTS_EQUAL ( eve::add[ t    ](tv, fv), tv+fv);
  TTS_EQUAL ( eve::add[ 0    ](tv, fv), tv);
  TTS_EQUAL ( eve::add[ 0.0  ](tv, fv), tv);
  TTS_EQUAL ( eve::add[ false](tv, fv), tv);
  TTS_EQUAL ( eve::add[ f    ](tv, fv), tv);
}

#endif
