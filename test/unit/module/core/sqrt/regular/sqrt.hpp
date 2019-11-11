//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqrt.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sqrt return type")
{
  TTS_EXPR_IS(eve::sqrt(Type(0)), (Type));
}

TTS_CASE("Check eve::sqrt behavior")
{
  TTS_EQUAL(eve::sqrt(eve::Mzero<Type>()) , (Type(0)));
  TTS_EQUAL(eve::sqrt(Type(0))            , (Type(0)));
  TTS_EQUAL(eve::sqrt(Type(1))            , (Type(1)));
  TTS_EQUAL(eve::sqrt(Type(4))            , (Type(2)));

  TTS_ULP_EQUAL(eve::sqrt(Type(2)), eve::Sqrt_2<Type>(), 0.5);
  TTS_IEEE_EQUAL(eve::sqrt( eve::Nan<Type>()), (eve::Nan<Type>()));
}
