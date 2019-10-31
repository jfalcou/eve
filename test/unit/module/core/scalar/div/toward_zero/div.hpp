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

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/scalar/div.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE( "Check div return type" )
{
  TTS_EXPR_IS(eve::div(Type(), Type(), eve::toward_zero_) , Type);
}

TTS_CASE("Check toward_zero (eve::div behavior")
{
  if constexpr(std::is_integral_v<Type>)
  {
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::div(eve::Mone<Type>(),   eve::Mone<Type>(), eve::toward_zero_), eve::One<Type>());
      TTS_EQUAL(eve::div(eve::One<Type>(),    eve::One<Type>() , eve::toward_zero_), eve::One<Type>());
      TTS_EQUAL(eve::div(eve::Valmax<Type>(), eve::Mone<Type>(), eve::toward_zero_), eve::Valmin<Type>()+eve::One<Type>());
      TTS_EQUAL(eve::div(eve::Valmax<Type>(), eve::One<Type>() , eve::toward_zero_), eve::Valmax<Type>());
      TTS_EQUAL(eve::div(eve::Valmin<Type>(), eve::Mone<Type>(), eve::toward_zero_), eve::Valmax<Type>());
      TTS_EQUAL(eve::div(eve::Zero<Type>(),   eve::Zero<Type>(), eve::toward_zero_), eve::Zero<Type>());
      TTS_EQUAL(eve::div(eve::Mone<Type>(),   eve::Zero<Type>(), eve::toward_zero_), eve::Valmin<Type>());
      TTS_EQUAL(eve::div(eve::Valmin<Type>(), eve::Zero<Type>(), eve::toward_zero_), eve::Valmin<Type>());
      TTS_EQUAL(eve::div(eve::One<Type>(),    eve::Zero<Type>(), eve::toward_zero_), eve::Valmax<Type>());
      TTS_EQUAL(eve::div(eve::Valmax<Type>(), eve::Zero<Type>(), eve::toward_zero_), eve::Valmax<Type>());
      TTS_EQUAL(eve::div(eve::Mone<Type>(),   Type(2), eve::toward_zero_), eve::Zero<Type>());
      TTS_EQUAL(eve::div(static_cast<Type>(-4), Type(3), eve::toward_zero_), static_cast<Type>(-1));
    }
    else
    {
      TTS_EQUAL(eve::div(eve::One<Type>()   , eve::One<Type>() , eve::toward_zero_)    , eve::One<Type>());
      TTS_EQUAL(eve::div(eve::Valmax<Type>(),eve::One<Type>()  , eve::toward_zero_)  , eve::Valmax<Type>());
      TTS_EQUAL(eve::div(eve::Zero<Type>()  , eve::Zero<Type>(), eve::toward_zero_)  , eve::Zero<Type>());
      TTS_EQUAL(eve::div(eve::One<Type>()   , eve::Zero<Type>(), eve::toward_zero_)   , eve::Valmax<Type>());
      TTS_EQUAL(eve::div(eve::Valmax<Type>(), eve::Zero<Type>(), eve::toward_zero_), eve::Valmax<Type>());
    }
  }
  else
  {
    TTS_EQUAL(eve::div(static_cast<Type>(-1) , Type{2}, eve::toward_zero_), Type(0));
    TTS_EQUAL(eve::div(static_cast<Type>(-4) , Type{3}, eve::toward_zero_), Type(-1));
  }
  
  TTS_EQUAL(eve::div(Type{0} , Type{1}, eve::toward_zero_), Type{0});
  TTS_EQUAL(eve::div(Type{1} , Type{1}, eve::toward_zero_), Type{1});
  TTS_EQUAL(eve::div(Type{12}, Type{4}, eve::toward_zero_), Type{3});
  TTS_EQUAL(eve::div(Type{1} , Type{2}, eve::toward_zero_), Type(0));
  TTS_EQUAL(eve::div(Type{4} , Type{3}, eve::toward_zero_), Type(1));
}

#endif
