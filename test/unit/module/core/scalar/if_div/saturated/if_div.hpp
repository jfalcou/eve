//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_DIV_HPP
#define IF_DIV_HPP

#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/div.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>
#include <eve/tags.hpp>

TTS_CASE( "Check saturated conditional div return type" )
{
  TTS_EXPR_IS(eve::saturated_(eve::div[Type()])( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::saturated_(eve::div[eve::logical<Type>()])( Type(), Type() ) , Type );
  TTS_EXPR_IS(eve::saturated_(eve::div[true])( Type(), Type() ) , Type );
}

TTS_CASE("Check  saturated conditional div behavior")
{
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();
  {
    Type tv{25};
    Type fv{3};
    TTS_EQUAL ( eve::saturated_(eve::div[ 1    ])(tv, fv), tv/fv);
    TTS_EQUAL ( eve::saturated_(eve::div[ 1.0  ])(tv, fv), tv/fv);
    TTS_EQUAL ( eve::saturated_(eve::div[ true ])(tv, fv), tv/fv);
    TTS_EQUAL ( eve::saturated_(eve::div[ t    ])(tv, fv), tv/fv);
    TTS_EQUAL ( eve::saturated_(eve::div[ 0    ])(tv, fv), tv);
    TTS_EQUAL ( eve::saturated_(eve::div[ 0.0  ])(tv, fv), tv);
    TTS_EQUAL ( eve::saturated_(eve::div[ false])(tv, fv), tv);
    TTS_EQUAL ( eve::saturated_(eve::div[ f    ])(tv, fv), tv);
  }

}
  
#endif
  
