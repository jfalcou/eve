//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_EQUAL_HPP
#define IS_EQUAL_HPP

#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_lessgreater.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check eve::is_lessgreater return type" )
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_lessgreater(Type()          , Type())         ,  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_lessgreater(logical<Type>() , Type())         ,  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_lessgreater(logical<Type>() , logical<Type>()),  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_lessgreater(Type()          , logical<Type>()),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_lessgreater behavior")
{
  using eve::logical;

  TTS_EQUAL(eve::is_lessgreater(Type(1),Type(1))                      , eve::False<Type>() );
  TTS_EQUAL(eve::is_lessgreater(Type(3),Type(1))                      , eve::True<Type>());
  TTS_EQUAL(eve::is_lessgreater(Type(3),Type(7))                      , eve::True<Type>());

  TTS_EQUAL(eve::is_lessgreater(eve::True<Type>()  , eve::True<Type>() ) , eve::False<Type>());
  TTS_EQUAL(eve::is_lessgreater(eve::True<Type>()  , eve::False<Type>()) , eve::True<Type>());
  TTS_EQUAL(eve::is_lessgreater(eve::False<Type>() , eve::True<Type>() ) , eve::True<Type>() );
  TTS_EQUAL(eve::is_lessgreater(eve::False<Type>() , eve::False<Type>()) , eve::False<Type>());
}

#endif
