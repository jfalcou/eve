//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_ORDERED_HPP
#define IS_ORDERED_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_ordered.hpp>
#include <type_traits>

TTS_CASE("Check is_ordered return type")
{
  TTS_EXPR_IS(eve::is_ordered(Type(), Type()), eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_ordered behavior on arithmetic")
{
  TTS_EQUAL(eve::is_ordered(Type(1), Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_ordered(Type(3), Type(1)), eve::True<Type>());
  TTS_EQUAL(eve::is_ordered(Type(1), Type(3)), eve::True<Type>());

  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_EQUAL(eve::is_ordered(eve::Nan<Type>(), Type(3)), eve::False<Type>());
    TTS_EQUAL(eve::is_ordered(Type(3), eve::Nan<Type>()), eve::False<Type>());
    TTS_EQUAL(eve::is_ordered(eve::Nan<Type>(), eve::Nan<Type>()), eve::False<Type>());
  }
}

TTS_CASE("Check eve::is_ordered behavior on logical")
{
  TTS_EQUAL(eve::is_ordered(eve::logical<Type>(1), eve::logical<Type>(0)), eve::True<Type>());
}

#endif

