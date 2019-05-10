//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_EQUAL_WITH_EQUAL_NANS_HPP
#define IS_EQUAL_WITH_EQUAL_NANS_HPP

#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_equal_with_equal_nans.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE( "Check eve::is_equal_with_equal_nans return type" )
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_equal_with_equal_nans(Type()          , Type())         ,  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_equal_with_equal_nans(logical<Type>() , Type())         ,  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_equal_with_equal_nans(logical<Type>() , logical<Type>()),  eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_equal_with_equal_nans(Type()          , logical<Type>()),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_equal_with_equal_nans_with_equal_nans behavior")
{
  using eve::logical;

  TTS_EQUAL(eve::is_equal_with_equal_nans(Type(1),Type(1))                      , eve::True<Type>() );
  TTS_EQUAL(eve::is_equal_with_equal_nans(Type(3),Type(1))                      , eve::False<Type>());

  TTS_EQUAL(eve::is_equal_with_equal_nans(eve::Nan<Type>(), eve::Nan<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::is_equal_with_equal_nans(eve::Nan<Type>(), Type(4)), eve::False<Type>());
  TTS_EQUAL(eve::is_equal_with_equal_nans(Type(7), eve::Nan<Type>() ), eve::False<Type>());

  TTS_EQUAL(eve::is_equal_with_equal_nans(eve::True<Type>(),Type(1))            , eve::True<Type>() );
  TTS_EQUAL(eve::is_equal_with_equal_nans(eve::False<Type>(),Type(1))           , eve::False<Type>());
  TTS_EQUAL(eve::is_equal_with_equal_nans(eve::True<Type>(),eve::True<Type>())  , eve::True<Type>() );
  TTS_EQUAL(eve::is_equal_with_equal_nans(eve::True<Type>(),eve::False<Type>()) , eve::False<Type>());
  TTS_EQUAL(eve::is_equal_with_equal_nans(Type(3),eve::True<Type>())            , eve::True<Type>() );
  TTS_EQUAL(eve::is_equal_with_equal_nans(Type(3),eve::False<Type>())           , eve::False<Type>());
}

#endif
