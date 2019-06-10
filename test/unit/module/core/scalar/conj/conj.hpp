//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CONJ_HPP
#define CONJ_HPP

#include <eve/function/scalar/conj.hpp>
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

TTS_CASE("Check conj return type")
{
  TTS_EXPR_IS(eve::conj(Type(0)),  Type);
}

TTS_CASE("Check eve::conj behavior")
{
  TTS_EQUAL(eve::conj(Type{1}), Type(1));
  TTS_EQUAL(eve::conj(Type{2}), Type(2));
  
  TTS_EQUAL(eve::conj(static_cast<Type>(-2)), Type(-2));
  TTS_IEEE_EQUAL(eve::conj(eve::Nan<Type>()), eve::Nan<Type>());
  TTS_IEEE_EQUAL(eve::conj(-eve::Nan<Type>()), -eve::Nan<Type>());
  TTS_EQUAL(eve::conj(eve::Mzero<Type>()), Type(0)); 
  TTS_EQUAL(eve::conj(eve::Zero<Type>()),  Type(0)); 
}
  
#endif
