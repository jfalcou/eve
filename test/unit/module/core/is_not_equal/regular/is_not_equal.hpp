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

#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_not_equal.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check eve::is_not_equal return type" )
{
  using eve::logical;
  TTS_EXPR_IS(eve::is_not_equal(Type()          , Type())         ,  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_not_equal(logical<Type>() , Type())         ,  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_not_equal(logical<Type>() , logical<Type>()),  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_not_equal(Type()          , logical<Type>()),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::operator!= return type")
{
  using eve::logical;

  TTS_EXPR_IS(logical<Type>() != Type(), eve::as_logical_t<Type>);
  TTS_EXPR_IS(logical<Type>() != logical<Type>(), eve::as_logical_t<Type>);
  TTS_EXPR_IS(Type() != logical<Type>(), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_not_equal behavior")
{
  using eve::logical;
  if constexpr(eve::platform::supports_nans && std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(eve::is_not_equal(eve::Nan<Type>(), eve::Nan<Type>())   , eve::True<Type>());
    TTS_EQUAL(eve::is_not_equal(eve::Nan<Type>(), Type(4))            , eve::True<Type>());
  }
  TTS_EQUAL(eve::is_not_equal(Type(1),Type(1))                      , eve::False<Type>() );
  TTS_EQUAL(eve::is_not_equal(Type(3),Type(1))                      , eve::True<Type>());
  TTS_EQUAL(eve::is_not_equal(Type(7), eve::Nan<Type>() )           , eve::True<Type>());
  TTS_EQUAL(eve::is_not_equal(eve::False<Type>(),Type(1))            , eve::True<Type>() );
  TTS_EQUAL(eve::is_not_equal(eve::True<Type>(),Type(1))           , eve::False<Type>());
  TTS_EQUAL(eve::is_not_equal(eve::False<Type>(),eve::False<Type>())  , eve::False<Type>() );
  TTS_EQUAL(eve::is_not_equal(eve::False<Type>(),eve::True<Type>()) , eve::True<Type>());
  TTS_EQUAL(eve::is_not_equal(Type(3),eve::False<Type>())            , eve::True<Type>() );
  TTS_EQUAL(eve::is_not_equal(Type(3),eve::True<Type>())           , eve::False<Type>());
}

TTS_CASE("Check eve::operator!= behavior")
{
  using eve::logical;

  TTS_EQUAL(eve::False<Type>() != Type(1), eve::True<Type>());
  TTS_EQUAL(eve::True<Type>() != Type(1), eve::False<Type>());
  TTS_EQUAL(eve::False<Type>() != eve::False<Type>(), eve::False<Type>());
  TTS_EQUAL(eve::False<Type>() != eve::True<Type>(), eve::True<Type>());
  TTS_EQUAL(Type(3) != eve::False<Type>(), eve::True<Type>());
  TTS_EQUAL(Type(3) != eve::True<Type>(), eve::False<Type>());
}
#endif

