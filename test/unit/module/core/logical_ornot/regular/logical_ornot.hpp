//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_ornot.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::logical_ornot return type")
{
  using eve::logical;

  TTS_EXPR_IS((eve::logical_ornot(Type()         , Type())         ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(logical<Type>(), Type())         ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(logical<Type>(), logical<Type>())), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(Type()         , logical<Type>())), (logical<Type>));

  TTS_EXPR_IS((eve::logical_ornot(Value()         , Type())           ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(Type()          , Value())          ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(logical<Type>() , Value())          ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(logical<Value>(), Type())           ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(logical<Value>(), logical<Type>())  ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(logical<Type>() , logical<Value>()) ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(Value()         , logical<Type>())  ), (logical<Type>));
  TTS_EXPR_IS((eve::logical_ornot(Type()          , logical<Value>()) ), (logical<Type>));
}

TTS_CASE("Check eve::logical_ornot behavior on scalars")
{
  TTS_EQUAL(eve::logical_ornot((Type(0)), (Type(0))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot((Type(0)), (Type(1))), eve::False<Type>());
  TTS_EQUAL(eve::logical_ornot((Type(2)), (Type(1))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot((Type(1)), (Type(0))), eve::True<Type>() );

  TTS_EQUAL(eve::logical_ornot(Value(0), (Type(0))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot(Value(0), (Type(1))), eve::False<Type>());
  TTS_EQUAL(eve::logical_ornot(Value(2), (Type(1))), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot(Value(1), (Type(0))), eve::True<Type>() );

  TTS_EQUAL(eve::logical_ornot((Type(0)), Value(0)), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot((Type(0)), Value(1)), eve::False<Type>());
  TTS_EQUAL(eve::logical_ornot((Type(2)), Value(1)), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot((Type(1)), Value(0)), eve::True<Type>() );
}

TTS_CASE("Check eve::logical_ornot behavior on logicals")
{
  TTS_EQUAL(eve::logical_ornot(eve::False<Type>() , eve::False<Type>()) , eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot(eve::False<Type>() , eve::True<Type>() ) , eve::False<Type>());
  TTS_EQUAL(eve::logical_ornot(eve::True<Type>()  , eve::True<Type>() ) , eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot(eve::True<Type>()  , eve::False<Type>()) , eve::True<Type>() );

  TTS_EQUAL(eve::logical_ornot(eve::False<Value>(), eve::False<Type>()), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot(eve::False<Value>(), eve::True<Type>() ), eve::False<Type>());
  TTS_EQUAL(eve::logical_ornot(eve::True<Value>() , eve::True<Type>() ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot(eve::True<Value>() , eve::False<Type>()), eve::True<Type>() );

  TTS_EQUAL(eve::logical_ornot(eve::False<Type>() , eve::False<Value>() ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot(eve::False<Type>() , eve::True<Value>()  ), eve::False<Type>());
  TTS_EQUAL(eve::logical_ornot(eve::True<Type>()  , eve::True<Value>()  ), eve::True<Type>() );
  TTS_EQUAL(eve::logical_ornot(eve::True<Type>()  , eve::False<Value>() ), eve::True<Type>() );
}
