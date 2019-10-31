//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_equal.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_equal return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_equal(Type()          , Type()          ), (logical<Type>));
  TTS_EXPR_IS(eve::is_equal(Type()          , Value()         ), (logical<Type>));
  TTS_EXPR_IS(eve::is_equal(Value()         , Type()          ), (logical<Type>));
  TTS_EXPR_IS(eve::is_equal(logical<Type>() , logical<Type>() ), (logical<Type>));
  TTS_EXPR_IS(eve::is_equal(logical<Type>() , logical<Value>()), (logical<Type>));
  TTS_EXPR_IS(eve::is_equal(logical<Value>(), logical<Type>() ), (logical<Type>));
}

TTS_CASE("Check eve::operator== return type")
{
  using eve::logical;

#if defined(EVE_SIMD_TESTS)
  TTS_EXPR_IS((Type()   == Type() ), (logical<Type>));
  TTS_EXPR_IS((Type()   == Value()), (logical<Type>));
  TTS_EXPR_IS((Value()  == Type() ), (logical<Type>));
#endif

  TTS_EXPR_IS((logical<Type>()  == logical<Type>() ), (logical<Type>));
  TTS_EXPR_IS((logical<Type>()  == logical<Value>()), (logical<Type>));
  TTS_EXPR_IS((logical<Value>() == logical<Type>() ), (logical<Type>));
}

TTS_CASE("Check eve::is_equal behavior")
{
  using eve::logical;

  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::is_equal(eve::Nan<Type>(), eve::Nan<Type>())   , eve::False<Type>());
    TTS_EQUAL(eve::is_equal(eve::Nan<Type>(), Type(4))            , eve::False<Type>());
  }

  TTS_EQUAL(eve::is_equal(Type(1)           , Type(1) )           , eve::True<Type>() );
  TTS_EQUAL(eve::is_equal(Type(1)           , Value(1))           , eve::True<Type>() );
  TTS_EQUAL(eve::is_equal(Type(3)           , Type(1) )           , eve::False<Type>());
  TTS_EQUAL(eve::is_equal(Type(3)           , Value(1))           , eve::False<Type>());
  TTS_EQUAL(eve::is_equal(eve::True<Type>() , eve::True<Type>())  , eve::True<Type>() );
  TTS_EQUAL(eve::is_equal(eve::True<Type>() , eve::False<Type>()) , eve::False<Type>());
}
TTS_CASE("Check eve::operator== behavior")
{
  using eve::logical;

  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Value>)
  {
    TTS_EQUAL((eve::Nan<Type>() == eve::Nan<Type>())   , eve::False<Type>());
    TTS_EQUAL((eve::Nan<Type>() == Type(4))            , eve::False<Type>());
  }

  TTS_EQUAL( (Type(1)           == Type(1) )           , eve::True<Type>() );
  TTS_EQUAL( (Type(1)           == Value(1))           , eve::True<Type>() );
  TTS_EQUAL( (Type(3)           == Type(1) )           , eve::False<Type>());
  TTS_EQUAL( (Type(3)           == Value(1))           , eve::False<Type>());
  TTS_EQUAL( (eve::True<Type>() == eve::True<Type>())  , eve::True<Type>() );
  TTS_EQUAL( (eve::True<Type>() == eve::False<Type>()) , eve::False<Type>());
}
