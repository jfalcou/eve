//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ADD_HPP
#define ADD_HPP

#include <eve/function/scalar/add.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/function/mul.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp> 
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE( "Check mul return type" )
{
  TTS_EXPR_IS(eve::mul[Type()]( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::mul[eve::logical<Type>()]( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::mul[true]( Type(), Type() ) , Type );
}

TTS_CASE("Check conditional mul behavior")
{
  Type tv{2};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();    
 
  TTS_EQUAL ( eve::mul[ 1    ](tv, fv), tv*fv);
  TTS_EQUAL ( eve::mul[ 1.0  ](tv, fv), tv*fv);
  TTS_EQUAL ( eve::mul[ true ](tv, fv), tv*fv);
  TTS_EQUAL ( eve::mul[ t    ](tv, fv), tv*fv);
  TTS_EQUAL ( eve::mul[ 0    ](tv, fv), tv);
  TTS_EQUAL ( eve::mul[ 0.0  ](tv, fv), tv);
  TTS_EQUAL ( eve::mul[ false](tv, fv), tv);
  TTS_EQUAL ( eve::mul[ f    ](tv, fv), tv);
}

#endif
