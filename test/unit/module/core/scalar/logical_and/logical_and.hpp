//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_AND_HPP
#define LOGICAL_AND_HPP

#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/scalar/logical_and.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check logical_and return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::logical_and(Type(), Type()), logical<Type>);
  TTS_EXPR_IS(eve::logical_and(logical<Type>(), Type()), logical<Type>);
  TTS_EXPR_IS(eve::logical_and(logical<Type>(), logical<Type>()), logical<Type>);
  TTS_EXPR_IS(eve::logical_and(Type(), logical<Type>()), logical<Type>);

  TTS_EXPR_IS(logical<Type>() && Type(), logical<Type>);
  TTS_EXPR_IS(logical<Type>() && logical<Type>(), logical<Type>);
  TTS_EXPR_IS(Type() && logical<Type>(), logical<Type>);
}

TTS_CASE("Check eve::logical_and behavior on scalars")
{
  TTS_EQUAL(eve::logical_and(Type{0}, Type{1}), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(Type{1}, Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(Type{2}, Type{1}), eve::True<Type>());
}

TTS_CASE("Check eve::logical_and behavior on logicals")
{
  TTS_EQUAL(eve::logical_and(eve::False<Type>(), eve::True<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Type>(), eve::False<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Type>(), eve::True<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::logical_and(eve::False<Type>(), eve::False<Type>()), eve::False<Type>());

  TTS_EQUAL(eve::logical_and(Type{0}, eve::True<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Type>(), Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(Type{7}, eve::True<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Type>(), Type{99}), eve::True<Type>());
}

TTS_CASE("Check eve::operator&& behavior on logicals")
{
  TTS_EQUAL(eve::False<Type>() && eve::True<Type>(), eve::False<Type>());
  TTS_EQUAL(eve::True<Type>() && eve::False<Type>(), eve::False<Type>());
  TTS_EQUAL(eve::True<Type>() && eve::True<Type>(), eve::True<Type>());
  TTS_EQUAL(eve::False<Type>() && eve::False<Type>(), eve::False<Type>());

  TTS_EQUAL(Type{0} && eve::True<Type>(), eve::False<Type>());
  TTS_EQUAL(eve::True<Type>() && Type{0}, eve::False<Type>());
  TTS_EQUAL(Type{7} && eve::True<Type>(), eve::True<Type>());
  TTS_EQUAL(eve::True<Type>() && Type{99}, eve::True<Type>());
}

#endif
