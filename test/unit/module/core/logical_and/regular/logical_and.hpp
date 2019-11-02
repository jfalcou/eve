//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_and.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::logical_and return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_and(Type()         , Type())         ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(logical<Type>(), Type())         ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(logical<Type>(), logical<Type>())), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(Type()         , logical<Type>())), (logical<Type>));

  TTS_EXPR_IS((eve::logical_and(Value()         , Type())           ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(Type()          , Value())          ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(logical<Type>() , Value())          ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(logical<Value>(), Type())           ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(logical<Value>(), logical<Type>())  ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(logical<Type>() , logical<Value>()) ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(Value()         , logical<Type>())  ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_and(Type()          , logical<Value>()) ), (logical<Type>));
}

TTS_CASE("Check eve::operator&& return type")
{
  using eve::logical;

  TTS_EXPR_IS((logical<Type>()  && Type()         ), (logical<Type>));
  TTS_EXPR_IS((logical<Type>()  && logical<Type>()), (logical<Type>));
  TTS_EXPR_IS((Type()           && logical<Type>()), (logical<Type>));
  TTS_EXPR_IS((logical<Type>()  && Value()        ), (logical<Type>));
  TTS_EXPR_IS((logical<Value>() && Type()         ), (logical<Type>));
}

TTS_CASE("Check eve::logical_and behavior on scalars")
{
  TTS_EQUAL(eve::logical_and((Type(0)), (Type(0))), eve::False<Type>());
  TTS_EQUAL(eve::logical_and((Type(0)), (Type(1))), eve::False<Type>());
  TTS_EQUAL(eve::logical_and((Type(2)), (Type(1))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_and((Type(1)), (Type(0))), eve::False<Type>());

  TTS_EQUAL(eve::logical_and(Value(0), (Type(0))), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(Value(0), (Type(1))), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(Value(2), (Type(1))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_and(Value(1), (Type(0))), eve::False<Type>());

  TTS_EQUAL(eve::logical_and((Type(0)), Value(0)), eve::False<Type>());
  TTS_EQUAL(eve::logical_and((Type(0)), Value(1)), eve::False<Type>());
  TTS_EQUAL(eve::logical_and((Type(2)), Value(1)), eve::True<Type>() );
  TTS_EQUAL(eve::logical_and((Type(1)), Value(0)), eve::False<Type>());
}

TTS_CASE("Check eve::logical_and behavior on logicals")
{
  TTS_EQUAL(eve::logical_and(eve::False<Type>() , eve::False<Type>()) , eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::False<Type>() , eve::True<Type>() ) , eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Type>()  , eve::True<Type>() ) , eve::True<Type>() );
  TTS_EQUAL(eve::logical_and(eve::True<Type>()  , eve::False<Type>()) , eve::False<Type>());

  TTS_EQUAL(eve::logical_and(eve::False<Value>(), eve::False<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::False<Value>(), eve::True<Type>() ), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Value>() , eve::True<Type>() ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_and(eve::True<Value>() , eve::False<Type>()), eve::False<Type>());

  TTS_EQUAL(eve::logical_and(eve::False<Type>() , eve::False<Value>() ), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::False<Type>() , eve::True<Value>()  ), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Type>()  , eve::True<Value>()  ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_and(eve::True<Type>()  , eve::False<Value>() ), eve::False<Type>());
}

TTS_CASE("Check eve::operator&& behavior on logicals")
{
  TTS_EQUAL(eve::False<Type>()  && eve::False<Type>(), eve::False<Type>());
  TTS_EQUAL(eve::False<Type>()  && eve::True<Type>() , eve::False<Type>());
  TTS_EQUAL(eve::True<Type>()   && eve::True<Type>() , eve::True<Type>() );
  TTS_EQUAL(eve::True<Type>()   && eve::False<Type>(), eve::False<Type>());

  TTS_EQUAL(eve::False<Value>() && eve::False<Type>(), eve::False<Type>());
  TTS_EQUAL(eve::False<Value>() && eve::True<Type>() , eve::False<Type>());
  TTS_EQUAL(eve::True<Value>()  && eve::True<Type>() , eve::True<Type>() );
  TTS_EQUAL(eve::True<Value>()  && eve::False<Type>(), eve::False<Type>());

  TTS_EQUAL(eve::False<Type>()  && eve::False<Value>(), eve::False<Type>());
  TTS_EQUAL(eve::False<Type>()  && eve::True<Value>() , eve::False<Type>());
  TTS_EQUAL(eve::True<Type>()   && eve::True<Value>() , eve::True<Type>() );
  TTS_EQUAL(eve::True<Type>()   && eve::False<Value>(), eve::False<Type>());
}
