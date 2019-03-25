//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_GREATER_EQUAL_HPP
#define IS_GREATER_EQUAL_HPP

#include <eve/function/scalar/is_greater_equal.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <type_traits>

TTS_CASE( "Check is_greater_equal return type" )
{
  TTS_EXPR_IS(eve::is_greater_equal(Type(), Type()) ,  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_greater_equal behavior")
{
  TTS_EQUAL(eve::is_greater_equal(Type(1),Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_greater_equal(Type(3),Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_greater_equal(Type(1),Type(3)), eve::False<Type>());
}

#endif
