//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXPONENT_HPP
#define EXPONENT_HPP

#include <eve/function/scalar/exponent.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp> 
#include <type_traits>

TTS_CASE("Check exponent return type") { TTS_EXPR_IS(eve::exponent(Type(0)), eve::detail::as_integer_t<Type>); }

TTS_CASE ("checking  exponent behaviour")
{
  // specific values tests
  TTS_EQUAL(eve::exponent(eve::Minf<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::exponent(eve::Inf <Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::exponent(eve::Nan <Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::exponent(eve::Mone<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::exponent(eve::One<Type>()),  eve::Zero<Type>());
  TTS_EQUAL(eve::exponent(eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::exponent(Type(2)),  eve::One<Type>() );
  TTS_EQUAL(eve::exponent(Type(1.5)),        eve::Zero<Type>() );
  TTS_EQUAL(eve::exponent(Type(4.5)),        Type(2)); 
}

#endif
