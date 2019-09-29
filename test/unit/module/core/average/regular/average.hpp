//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include <eve/function/scalar/average.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/mone.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>  
#include <type_traits>

TTS_CASE("Check average return type")
{
  TTS_EXPR_IS(eve::average(Type(), Type()), Type);
}

TTS_CASE("Check  eve::average behaviour")
{
  TTS_EQUAL(eve::average(eve::One<Type>(),  eve::One<Type>()),  eve::One<Type>());
  TTS_EQUAL(eve::average(eve::Zero<Type>(), eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::average(eve::One <Type>(), Type(3))          , Type(2)); 
  TTS_EQUAL(eve::average(eve::Valmax<Type>(), eve::Valmax<Type>()), eve::Valmax<Type>()); 
  TTS_EQUAL(eve::average(eve::Valmin<Type>(), eve::Valmin<Type>()), eve::Valmin<Type>()); 
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::average(eve::Mone<Type>(), eve::Mone<Type>()), eve::Mone<Type>());
  }
}

#endif
