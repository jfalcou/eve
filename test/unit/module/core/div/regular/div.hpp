//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check eve::div return type")
{
  TTS_EXPR_IS(eve::div(Type(), Type()), (Type));
}

TTS_CASE("Check eve::div behavior")
{
  TTS_EQUAL(eve::div(Type( 0), Type(1)), (Type(0  )));
  TTS_EQUAL(eve::div(Type( 1), Type(1)), (Type(1  )));
  TTS_EQUAL(eve::div(Type(12), Type(4)), (Type(3  )));
  TTS_EQUAL(eve::div(Type( 1), Type(2)), (Type(0.5)));
  
  TTS_EQUAL(eve::div(Value( 0), Type(1)), (Type(0  )));
  TTS_EQUAL(eve::div(Value( 1), Type(1)), (Type(1  )));
  TTS_EQUAL(eve::div(Value(12), Type(4)), (Type(3  )));
  TTS_EQUAL(eve::div(Value( 1), Type(2)), (Type(0.5)));
  
  TTS_EQUAL(eve::div(Type( 0), Value(1)), (Type(0  )));
  TTS_EQUAL(eve::div(Type( 1), Value(1)), (Type(1  )));
  TTS_EQUAL(eve::div(Type(12), Value(4)), (Type(3  )));
  TTS_EQUAL(eve::div(Type( 1), Value(2)), (Type(0.5)));
  
  if constexpr(std::is_integral_v<Value>)
  {
    using i_t =  eve::detail::as_integer_t<Value>; 
    TTS_EQUAL(eve::div(eve::Valmax<Type>(), Type(2)), Type(eve::Valmax<i_t>() >> 1));
    TTS_EQUAL(eve::div(eve::Valmax<Value>(), Type(2)), Type(eve::Valmax<i_t>() >> 1));
    TTS_EQUAL(eve::div(eve::Valmax<Type>(), Value(2)), Type(eve::Valmax<i_t>() >> 1));  

    TTS_EQUAL(eve::div(eve::Valmax<Type>(), Type(1)), Type(eve::Valmax<i_t>())); 
    TTS_EQUAL(eve::div(eve::Valmax<Value>(), Type(1)), Type(eve::Valmax<i_t>()));
    TTS_EQUAL(eve::div(eve::Valmax<Type>(), Value(1)), Type(eve::Valmax<i_t>()));  
  }
  
  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::div(Type(-1), Type(1)) , (Type(-1)));
    TTS_EQUAL(eve::div(Type(-6), Type(-2)), (Type( 3)));
    
    TTS_EQUAL(eve::div(Value(-1), Type(1)) , (Type(-1)));
    TTS_EQUAL(eve::div(Value(-6), Type(-2)), (Type( 3)));
    
    TTS_EQUAL(eve::div(Type(-1), Value(1)) , (Type(-1)));
    TTS_EQUAL(eve::div(Type(-6), Value(-2)), (Type( 3)));
  }
}
