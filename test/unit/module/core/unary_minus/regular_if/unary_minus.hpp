//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef UNARY_MINUS_HPP
#define UNARY_MINUS_HPP

#include <eve/function/unary_minus.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>
#include <type_traits>

TTS_CASE("Check conditional unary_minus return type")
{
  TTS_EXPR_IS(eve::unary_minus[ Type() ](Type()), Type);
  TTS_EXPR_IS(eve::unary_minus[ eve::logical<Type>() ](Type()), Type);
  TTS_EXPR_IS(eve::unary_minus[ true ](Type()), Type);
}

TTS_CASE("Check conditional unary_minus behavior")
{
  Type tv{2};
  Type fv{3};
  auto t = eve::True<Type>();
  auto f = eve::False<Type>();

  TTS_EQUAL(eve::unary_minus[ 1 ](tv, fv), -tv);
  TTS_EQUAL(eve::unary_minus[ 1.0 ](tv, fv), -tv);
  TTS_EQUAL(eve::unary_minus[ true ](tv, fv), -tv);
  TTS_EQUAL(eve::unary_minus[ t ](tv, fv), -tv);
  TTS_EQUAL(eve::unary_minus[ 0 ](tv, fv), tv);
  TTS_EQUAL(eve::unary_minus[ 0.0 ](tv, fv), tv);
  TTS_EQUAL(eve::unary_minus[ false ](tv, fv), tv);
  TTS_EQUAL(eve::unary_minus[ f ](tv, fv), tv);
}

#endif
