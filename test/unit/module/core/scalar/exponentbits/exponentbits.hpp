//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXPONENTBITS_HPP
#define EXPONENTBITS_HPP

#include <eve/function/scalar/exponentbits.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrtvalmax.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/inc.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check exponentbits return type") { TTS_EXPR_IS(eve::exponentbits(Type(0)), Type); }

TTS_CASE("Check eve::exponentbits behavior")
{
  TTS_EQUAL(eve::exponentbits(Type{1}), eve::Zero<Type>());
  TTS_EQUAL(eve::exponentbits(Type{2}), eve::Zero<Type>());

  TTS_EQUAL(eve::exponentbits(static_cast<Type>(-2)), eve::Pi<Type>());
  TTS_IEEE_EQUAL(eve::exponentbits(eve::Nan<Type>()), eve::Pi<Type>());
  TTS_IEEE_EQUAL(eve::exponentbits(-eve::Nan<Type>()), eve::Zero<Type>());
  TTS_IEEE_EQUAL(eve::pedantic_(eve::exponentbits)(eve::Nan<Type>()), eve::Nan<Type>());
  TTS_IEEE_EQUAL(eve::pedantic_(eve::exponentbits)(-eve::Nan<Type>()), -eve::Nan<Type>());
  TTS_EQUAL(eve::exponentbits(eve::Mzero<Type>()), eve::Pi<Type>());
  TTS_EQUAL(eve::exponentbits(eve::Zero<Type>()), eve::Zero<Type>());
}

#endif
