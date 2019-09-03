//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_LESS_HPP
#define IS_NOT_LESS_HPP

#include "test.hpp"
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_not_less.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::is_not_less return type")
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_not_less(Type(), Type()), eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_not_less(logical<Type>(), Type()), eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_not_less(logical<Type>(), logical<Type>()), eve::as_logical_t<Type>);
  TTS_EXPR_IS(eve::is_not_less(Type(), logical<Type>()), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_not_less behavior")
{
  using eve::logical;

  TTS_EQUAL(eve::is_not_less(Type(1), Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Type(3), Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(Type(3), Type(7)), eve::False<Type>());

  TTS_EQUAL(eve::is_not_less(eve::True<Type>(), eve::True<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(eve::True<Type>(), eve::False<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::is_not_less(eve::False<Type>(), eve::True<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::is_not_less(eve::False<Type>(), eve::False<Type>()), eve::True<Type>());
}

#endif
