//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_less_equal.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_less_equal return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_less_equal(Type() , Type()  ), (logical<Type>));
  TTS_EXPR_IS(eve::is_less_equal(Type() , Value() ), (logical<Type>));
  TTS_EXPR_IS(eve::is_less_equal(Value(), Type()  ), (logical<Type>));
}

#if defined(EVE_SIMD_TESTS)
TTS_CASE("Check eve::operator<= return type")
{
  using eve::logical;

  TTS_EXPR_IS((Type()   <= Type() ), (logical<Type>));
  TTS_EXPR_IS((Type()   <= Value()), (logical<Type>));
  TTS_EXPR_IS((Value()  <= Type() ), (logical<Type>));
}
#endif

TTS_CASE("Check eve::is_less_equal behavior")
{
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_less_equal(Type(1), eve::Nan<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_less_equal(eve::Nan<Type>(), Type(1)), eve::False<Type>());
  }

  TTS_EQUAL(eve::is_less_equal(Type(1) , Type(1) ), eve::True<Type>());
  TTS_EQUAL(eve::is_less_equal(Type(1) , Value(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_less_equal(Value(1), Type(1) ), eve::True<Type>());
  TTS_EQUAL(eve::is_less_equal(Type(3) , Type(1) ), eve::False<Type>());
  TTS_EQUAL(eve::is_less_equal(Type(3) , Value(1)), eve::False<Type>());
  TTS_EQUAL(eve::is_less_equal(Value(3), Type(1) ), eve::False<Type>());
  TTS_EQUAL(eve::is_less_equal(Type(1) , Type(3) ), eve::True<Type>() );
  TTS_EQUAL(eve::is_less_equal(Type(1) , Value(3)), eve::True<Type>() );
  TTS_EQUAL(eve::is_less_equal(Value(1), Type(3) ), eve::True<Type>() );
}

TTS_CASE("Check eve::operator< behavior")
{
  using eve::logical;

  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Value>)
  {
    TTS_EQUAL((eve::Nan<Type>() <= eve::Nan<Type>()) , eve::False<Type>());
    TTS_EQUAL((eve::Nan<Type>() <= Type(4))          , eve::False<Type>());
  }

  TTS_EQUAL( (Type(1)   <= Type(1) ) , eve::True<Type>());
  TTS_EQUAL( (Value(1)  <= Type(1) ) , eve::True<Type>());
  TTS_EQUAL( (Type(1)   <= Value(1)) , eve::True<Type>());
  TTS_EQUAL( (Type(3)   <= Type(1) ) , eve::False<Type>());
  TTS_EQUAL( (Value(3)  <= Type(1) ) , eve::False<Type>());
  TTS_EQUAL( (Type(3)   <= Value(1)) , eve::False<Type>());
  TTS_EQUAL( (Type(1)   <= Type(3) ) , eve::True<Type>() );
  TTS_EQUAL( (Value(1)  <= Type(3) ) , eve::True<Type>() );
  TTS_EQUAL( (Type(1)   <= Value(3)) , eve::True<Type>() );
}
