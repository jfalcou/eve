//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ELSE_HPP
#define IF_ELSE_HPP

#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/logical.hpp>

TTS_CASE("Check if_else(., allbits_, .) return type")
{
  TTS_EXPR_IS(eve::if_else(Type(), eve::allbits_, Type()), Type);
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>(), eve::allbits_, Type()), Type);
  TTS_EXPR_IS(eve::if_else(true, eve::allbits_, Type()), Type);

  TTS_EXPR_IS(eve::if_else(Type(), Type(), eve::allbits_), Type);
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>(), Type(), eve::allbits_), Type);
  TTS_EXPR_IS(eve::if_else(true, Type(), eve::allbits_), Type);
}

TTS_CASE("Check if_else(., allbits_, .) behavior ")
{
  auto f = eve::Allbits<Type>();
  auto t = eve::One<Type>();

  TTS_IEEE_EQUAL(eve::if_else(1, eve::allbits_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(1.0, eve::allbits_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(true, eve::allbits_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<Type>(), eve::allbits_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(0, eve::allbits_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(0.0, eve::allbits_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(false, eve::allbits_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<Type>(), eve::allbits_, t), t);

  TTS_IEEE_EQUAL(eve::if_else(1, t, eve::allbits_), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0, t, eve::allbits_), t);
  TTS_IEEE_EQUAL(eve::if_else(true, t, eve::allbits_), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<Type>(), t, eve::allbits_), t);
  TTS_IEEE_EQUAL(eve::if_else(0, t, eve::allbits_), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0, t, eve::allbits_), f);
  TTS_IEEE_EQUAL(eve::if_else(false, t, eve::allbits_), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<Type>(), t, eve::allbits_), f);
}


#endif
