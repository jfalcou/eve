//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_EQUAL_HPP
#define IS_NOT_EQUAL_HPP

#include <eve/function/scalar/is_not_equal.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <type_traits>

TTS_CASE( "Check is_not_equal return type" )
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_not_equal(Type()          , Type())         , eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_not_equal(logical<Type>() , logical<Type>()), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_not_equal behavior")
{
  TTS_EQUAL(eve::is_not_equal(Type(1),Type(1)), eve::False<Type>());
  TTS_EQUAL(eve::is_not_equal(Type(3),Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_equal(Type(1),Type(3)), eve::True<Type>());

  TTS_EQUAL(eve::is_not_equal(Type(1)           , eve::True<Type>() ), eve::False<Type>() );
  TTS_EQUAL(eve::is_not_equal(Type(3)           , eve::False<Type>()), eve::True<Type>()  );
  TTS_EQUAL(eve::is_not_equal(eve::True<Type>() , Type(3)           ), eve::False<Type>() );
  TTS_EQUAL(eve::is_not_equal(eve::False<Type>(), Type(3)           ), eve::True<Type>()  );
  TTS_EQUAL(eve::is_not_equal(eve::True<Type>() , eve::True<Type>() ), eve::False<Type>() );
  TTS_EQUAL(eve::is_not_equal(eve::False<Type>(), eve::True<Type>() ), eve::True<Type>()  );
}

#endif
