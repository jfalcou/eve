//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IFNOT_ELSE_HPP
#define IFNOT_ELSE_HPP

#include <eve/function/scalar/ifnot_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>

TTS_CASE("Check ifnot_else return type")
{
  TTS_EXPR_IS(eve::ifnot_else(Type(), Type(), Type()), Type);
  TTS_EXPR_IS(eve::ifnot_else(eve::logical<Type>(), Type(), Type()), Type);
  TTS_EXPR_IS(eve::ifnot_else(true, Type(), Type()), Type);
}

TTS_CASE("Check ifnot_else behavior with arithmetic alternatives")
{
  Type tv{2};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::ifnot_else(1, tv, fv), fv);
  TTS_EQUAL(eve::ifnot_else(1.0, tv, fv), fv);
  TTS_EQUAL(eve::ifnot_else(true, tv, fv), fv);
  TTS_EQUAL(eve::ifnot_else(t, tv, fv), fv);
  TTS_EQUAL(eve::ifnot_else(0, tv, fv), tv);
  TTS_EQUAL(eve::ifnot_else(0.0, tv, fv), tv);
  TTS_EQUAL(eve::ifnot_else(false, tv, fv), tv);
  TTS_EQUAL(eve::ifnot_else(f, tv, fv), tv);
}

TTS_CASE("Check ifnot_else behavior with logical alternatives")
{
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::ifnot_else(1, t, f), f);
  TTS_EQUAL(eve::ifnot_else(1.0, t, f), f);
  TTS_EQUAL(eve::ifnot_else(true, t, f), f);
  TTS_EQUAL(eve::ifnot_else(t, t, f), f);
  TTS_EQUAL(eve::ifnot_else(0, t, f), t);
  TTS_EQUAL(eve::ifnot_else(0.0, t, f), t);
  TTS_EQUAL(eve::ifnot_else(false, t, f), t);
  TTS_EQUAL(eve::ifnot_else(f, t, f), t);
}

#endif
