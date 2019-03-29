//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_AND_HPP
#define LOGICAL_AND_HPP

#include <eve/function/scalar/logical_and.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp> 
#include <type_traits>

TTS_CASE( "Check logical_and return type" )
{
  TTS_EXPR_IS(eve::logical_and(Type(), Type()) ,  eve::as_logical_t<Type>);
  using l_t = eve::as_logical_t<Type>; 
  TTS_EXPR_IS(eve::logical_and(l_t(), l_t()) ,  eve::as_logical_t<Type>);   
}

TTS_CASE("Check eve::logical_and behavior")
{
  TTS_EQUAL(eve::logical_and(Type{0}, Type{1}), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(Type{1}, Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(Type{2}, Type{1}), eve::True<Type>());
}

TTS_CASE("Check eve::logical_and behavior on logicals")
{
  TTS_EQUAL(eve::logical_and(eve::False<Type>(), eve::True<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Type>(), eve::False<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::logical_and(eve::True<Type>(), eve::True<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::logical_and(eve::False<Type>(), eve::False<Type>()), eve::False<Type>());
}

#endif
