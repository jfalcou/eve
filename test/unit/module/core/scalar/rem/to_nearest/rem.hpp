//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REM_HPP
#define REM_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/scalar/rem.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE( "Check rem return type" )
{
  TTS_EXPR_IS(eve::rem(Type(), Type(), eve::to_nearest_) , Type);
}

TTS_CASE("Check eve::saturated_(eve::rem) behavior")
{
  if constexpr(std::is_integral_v<Type>)
  {
    if constexpr(std::is_signed_v<Type>)
    {
      TTS_EQUAL(eve::rem(eve::Mone<Type>(),   eve::Mone<Type>(), eve::to_nearest_), eve::Zero<Type>());
      TTS_EQUAL(eve::rem(eve::One<Type>(),    eve::One<Type>() , eve::to_nearest_), eve::Zero<Type>());
      TTS_EQUAL(eve::rem(eve::Valmax<Type>(), eve::Mone<Type>(), eve::to_nearest_), eve::Zero<Type>());
      TTS_EQUAL(eve::rem(eve::Valmax<Type>(), eve::One<Type>() , eve::to_nearest_), eve::Zero<Type>());
      TTS_EQUAL(eve::rem(eve::Mone<Type>(),   Type(2), eve::to_nearest_), Type(-1));
    }
    else
    {
      TTS_EQUAL(eve::rem(eve::One<Type>()   , eve::One<Type>() , eve::to_nearest_)    , eve::Zero<Type>());
      TTS_EQUAL(eve::rem(eve::Valmax<Type>(),eve::One<Type>()  , eve::to_nearest_)  , eve::Zero<Type>());
    }
  }
  else
  {
    TTS_EQUAL(eve::rem(static_cast<Type>(-1) , Type{2}, eve::to_nearest_), Type(-1));
    TTS_EQUAL(eve::rem(static_cast<Type>(-4) , Type{3}, eve::to_nearest_), Type(-1));
    TTS_EQUAL(eve::rem(static_cast<Type>(-5) , Type{3}, eve::to_nearest_), Type(1));
   }
  
  TTS_EQUAL(eve::rem(Type{0} , Type{1}, eve::to_nearest_), Type{0});
  TTS_EQUAL(eve::rem(Type{1} , Type{1}, eve::to_nearest_), Type{0});
  TTS_EQUAL(eve::rem(Type{12}, Type{4}, eve::to_nearest_), Type{0});
  TTS_EQUAL(eve::rem(Type{1} , Type{2}, eve::to_nearest_), Type(1));
  TTS_EQUAL(eve::rem(Type{4} , Type{3}, eve::to_nearest_), Type(1));
  TTS_EQUAL(eve::rem(Type{5} , Type{3}, eve::to_nearest_), Type(-1));
}

#endif
