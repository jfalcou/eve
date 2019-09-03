//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ELSE_MONE_HPP
#define IF_ELSE_MONE_HPP

#include <eve/function/scalar/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mone.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE("Check if_else return type")
{
  TTS_EXPR_IS(eve::if_else(Type(), Type(), eve::mone_), Type);
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>(), Type(), eve::mone_), Type);
  TTS_EXPR_IS(eve::if_else(true, Type(), eve::mone_), Type);
}

TTS_CASE("Check if_else(., ., mone_) behavior ")
{
  auto f = eve::Mone<Type>();
  auto t = eve::Mone<Type>();

  TTS_IEEE_EQUAL(eve::if_else(1, t, eve::mone_), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0, t, eve::mone_), t);
  TTS_IEEE_EQUAL(eve::if_else(true, t, eve::mone_), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<Type>(), t, eve::mone_), t);
  TTS_IEEE_EQUAL(eve::if_else(0, t, eve::mone_), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0, t, eve::mone_), f);
  TTS_IEEE_EQUAL(eve::if_else(false, t, eve::mone_), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<Type>(), t, eve::mone_), f);
}

#endif
