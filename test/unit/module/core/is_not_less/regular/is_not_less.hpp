//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_less.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_not_less return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_not_less(Type() , Type()  ), (logical<Type>));
  TTS_EXPR_IS(eve::is_not_less(Type() , Value() ), (logical<Type>));
  TTS_EXPR_IS(eve::is_not_less(Value(), Type()  ), (logical<Type>));
}

TTS_CASE("Check eve::is_not_less behavior")
{
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_not_less(Type(1), eve::Nan<Type>()), eve::True<Type>());
    TTS_EQUAL(eve::is_not_less(eve::Nan<Type>(), Type(1)), eve::True<Type>());
  }

  TTS_EQUAL(eve::is_not_less(Type(1) , Type(1) ), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Type(1) , Value(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Value(1), Type(1) ), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Type(3) , Type(1) ), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Type(3) , Value(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Value(3), Type(1) ), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Type(1) , Type(3) ), eve::False<Type>() );
  TTS_EQUAL(eve::is_not_less(Type(1) , Value(3)), eve::False<Type>() );
  TTS_EQUAL(eve::is_not_less(Value(1), Type(3) ), eve::False<Type>() );
}
