//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_NOTAND_HPP
#define LOGICAL_NOTAND_HPP

#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/scalar/logical_notand.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check logical_notand return type" )
{
  using eve::logical;

  TTS_EXPR_IS(eve::logical_notand(Type()         , Type()          ), logical<Type>);
  TTS_EXPR_IS(eve::logical_notand(logical<Type>(), Type()          ), logical<Type>);
  TTS_EXPR_IS(eve::logical_notand(logical<Type>(), logical<Type>() ), logical<Type>);
  TTS_EXPR_IS(eve::logical_notand(Type()         , logical<Type>() ), logical<Type>);
}

TTS_CASE("Check eve::logical_notand behavior on scalars")
{
  TTS_EQUAL(eve::logical_notand(Type{0}, Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::logical_notand(Type{0}, Type{1}), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notand(Type{2}, Type{3}), eve::False<Type>());
  TTS_EQUAL(eve::logical_notand(Type{4}, Type{0}), eve::False<Type>());
}

TTS_CASE("Check eve::logical_notand behavior on logicals")
{
  TTS_EQUAL(eve::logical_notand(eve::False<Type>(), eve::False<Type>()) , eve::False<Type>());
  TTS_EQUAL(eve::logical_notand(eve::False<Type>(), eve::True<Type>() ) , eve::True<Type>() );
  TTS_EQUAL(eve::logical_notand(eve::True<Type>() , eve::True<Type>() ) , eve::False<Type>());
  TTS_EQUAL(eve::logical_notand(eve::True<Type>() , eve::False<Type>()) , eve::False<Type>());

  TTS_EQUAL(eve::logical_notand(Type{0}           , eve::False<Type>()) , eve::False<Type>());
  TTS_EQUAL(eve::logical_notand(eve::False<Type>(), Type{1}           ) , eve::True<Type>() );
  TTS_EQUAL(eve::logical_notand(Type{2}           , eve::True<Type>() ) , eve::False<Type>());
  TTS_EQUAL(eve::logical_notand(eve::True<Type>() , Type{0}           ) , eve::False<Type>());
}

#endif
