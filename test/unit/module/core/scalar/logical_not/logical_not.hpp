//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_NOT_HPP
#define LOGICAL_NOT_HPP

#include "test.hpp"
#include <eve/constant/allbits.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/scalar/logical_not.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check logical_not return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::logical_not(Type())          , logical<Type>);
  TTS_EXPR_IS(eve::logical_not(logical<Type>()) , logical<Type>);
}

TTS_CASE("Check eve::logical_not behavior")
{
  TTS_EQUAL(eve::logical_not(Type(1))             , eve::False<Type>());
  TTS_EQUAL(eve::logical_not(Type(0))             , eve::True<Type>());
  TTS_EQUAL(eve::logical_not(eve::Allbits<Type>()), eve::False<Type>());
}

TTS_CASE("Check eve::logical_not behavior on logicals")
{
  TTS_EQUAL(eve::logical_not(eve::True<Type>()) , eve::False<Type>());
  TTS_EQUAL(eve::logical_not(eve::False<Type>()), eve::True<Type>());
}

TTS_CASE("Check eve::operator! behavior on logicals")
{
  TTS_EQUAL(!eve::True<Type>()  , eve::False<Type>());
  TTS_EQUAL(!eve::False<Type>() , eve::True<Type>());
}

#endif
