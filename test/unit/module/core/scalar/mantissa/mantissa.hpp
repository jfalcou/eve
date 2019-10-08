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
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/mone.hpp> 
#include <type_traits>

TTS_CASE("Check mantissa return type") { TTS_EXPR_IS(eve::mantissa(Type(0)), Type); }

TTS_CASE ("checking  mantissa behaviour")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::mantissa(eve::Inf<Type>()), eve::Inf<Type>());
    TTS_EQUAL(eve::mantissa(eve::Minf<Type>()), eve::Minf<Type>());
    TTS_IEEE_EQUAL(eve::mantissa(eve::Nan<Type>()), eve::Nan<Type>());
  }
  TTS_EQUAL(eve::mantissa(eve::Mone<Type>()), eve::Mone<Type>());
  TTS_EQUAL(eve::mantissa(eve::One<Type>()), eve::One<Type>());
  TTS_EQUAL(eve::mantissa(eve::Zero<Type>()), eve::Zero<Type>());
  TTS_EQUAL(eve::mantissa(Type(2)), eve::One<Type>());
  TTS_EQUAL(eve::mantissa(Type(1.5)), Type(1.5));
  TTS_EQUAL(eve::mantissa(Type(2.5)), Type(1.25));
}

#endif
