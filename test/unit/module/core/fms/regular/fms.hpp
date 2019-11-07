//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::fms return type")
{
  TTS_EXPR_IS(eve::fms(Type(), Type(), Type()), (Type));
}

TTS_CASE("Check eve::fms behavior")
{
  TTS_EQUAL(eve::fms(Type(0), Type(0), Type(0)), (Type(0)));
  TTS_EQUAL(eve::fms(Type(2), Type(5), Type(7)), (Type(3)));
  TTS_EQUAL(eve::fms(Type(8), Type(5), Type(7)), (Type(33)));
}

