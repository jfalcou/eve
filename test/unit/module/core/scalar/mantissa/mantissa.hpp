//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MANTISSA_HPP
#define MANTISSA_HPP

#include <eve/function/scalar/mantissa.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp> 
#include <type_traits>

TTS_CASE("Check mantissa return type") { TTS_EXPR_IS(eve::mantissa(Type(0)), eve::detail::as_integer_t<Type>); }

TTS_CASE ("checking  mantissa behaviour")
{
  // specific values tests
  TTS_EQUAL(eve::mantissa(eve::Minf<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::mantissa(eve::Inf <Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::mantissa(eve::Nan <Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::mantissa(eve::Mone<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::mantissa(eve::One<Type>()),  eve::Zero<Type>());
  TTS_EQUAL(eve::mantissa(eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::mantissa(Type(2)),  eve::One<Type>() );
  TTS_EQUAL(eve::mantissa(Type(1.5)),        eve::Zero<Type>() );
  TTS_EQUAL(eve::mantissa(Type(4.5)),        Type(2)); 
}

#endif
