//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_notor.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::logical_notor return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_notor(Type()         , Type())         ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(logical<Type>(), Type())         ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(logical<Type>(), logical<Type>())), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(Type()         , logical<Type>())), (logical<Type>));

  TTS_EXPR_IS((eve::logical_notor(Value()         , Type())           ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(Type()          , Value())          ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(logical<Type>() , Value())          ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(logical<Value>(), Type())           ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(logical<Value>(), logical<Type>())  ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(logical<Type>() , logical<Value>()) ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(Value()         , logical<Type>())  ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_notor(Type()          , logical<Value>()) ), (logical<Type>));
}

TTS_CASE("Check eve::logical_notor behavior on scalars")
{
  TTS_EQUAL(eve::logical_notor((Type(0)), (Type(0))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor((Type(0)), (Type(1))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor((Type(2)), (Type(1))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor((Type(1)), (Type(0))), eve::False<Type>());

  TTS_EQUAL(eve::logical_notor(Value(0), (Type(0))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(Value(0), (Type(1))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(Value(2), (Type(1))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(Value(1), (Type(0))), eve::False<Type>());

  TTS_EQUAL(eve::logical_notor((Type(0)), Value(0)), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor((Type(0)), Value(1)), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor((Type(2)), Value(1)), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor((Type(1)), Value(0)), eve::False<Type>());
}

TTS_CASE("Check eve::logical_notor behavior on logicals")
{
  TTS_EQUAL(eve::logical_notor(eve::False<Type>() , eve::False<Type>()) , eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::False<Type>() , eve::True<Type>() ) , eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::True<Type>()  , eve::True<Type>() ) , eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::True<Type>()  , eve::False<Type>()) , eve::False<Type>());

  TTS_EQUAL(eve::logical_notor(eve::False<Value>(), eve::False<Type>()), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::False<Value>(), eve::True<Type>() ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::True<Value>() , eve::True<Type>() ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::True<Value>() , eve::False<Type>()), eve::False<Type>());

  TTS_EQUAL(eve::logical_notor(eve::False<Type>() , eve::False<Value>() ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::False<Type>() , eve::True<Value>()  ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::True<Type>()  , eve::True<Value>()  ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_notor(eve::True<Type>()  , eve::False<Value>() ), eve::False<Type>());
}
