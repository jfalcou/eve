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

#include <eve/function/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE("Check if_else return type")
{
  TTS_EXPR_IS(eve::if_else(Type(), Type(), Type()), Type);
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>(), Type(), Type()), Type);
  TTS_EXPR_IS(eve::if_else(true, Type(), Type()), Type);
}

TTS_CASE("Check if_else behavior with arithmetic alternatives")
{
  Type tv{2};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::if_else(1, tv, fv), tv);
  TTS_EQUAL(eve::if_else(1.0, tv, fv), tv);
  TTS_EQUAL(eve::if_else(true, tv, fv), tv);
  TTS_EQUAL(eve::if_else(t, tv, fv), tv);
  TTS_EQUAL(eve::if_else(0, tv, fv), fv);
  TTS_EQUAL(eve::if_else(0.0, tv, fv), fv);
  TTS_EQUAL(eve::if_else(false, tv, fv), fv);
  TTS_EQUAL(eve::if_else(f, tv, fv), fv);
}

TTS_CASE("Check if_else behavior with logical alternatives")
{
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::if_else(1, t, f), t);
  TTS_EQUAL(eve::if_else(1.0, t, f), t);
  TTS_EQUAL(eve::if_else(true, t, f), t);
  TTS_EQUAL(eve::if_else(t, t, f), t);
  TTS_EQUAL(eve::if_else(0, t, f), f);
  TTS_EQUAL(eve::if_else(0.0, t, f), f);
  TTS_EQUAL(eve::if_else(false, t, f), f);
  TTS_EQUAL(eve::if_else(f, t, f), f);
}

#endif
