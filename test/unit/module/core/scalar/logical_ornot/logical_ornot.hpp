//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_ORNOT_HPP
#define LOGICAL_ORNOT_HPP

#include <eve/function/scalar/logical_ornot.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp> 
#include <type_traits>

TTS_CASE( "Check logical_ornot return type" )
{
  TTS_EXPR_IS(eve::logical_ornot(Type(), Type()) ,  eve::as_logical_t<Type>);
  using l_t = eve::as_logical_t<Type>; 
  TTS_EXPR_IS(eve::logical_ornot(l_t(), l_t()) ,  eve::as_logical_t<Type>);   
}

TTS_CASE("Check eve::logical_ornot behavior")
{
  TTS_EQUAL(eve::logical_ornot(Type{0}, Type{1}), eve::False<Type>());
  TTS_EQUAL(eve::logical_ornot(Type{1}, Type{0}), eve::True<Type>());
  TTS_EQUAL(eve::logical_ornot(Type{2}, Type{1}), eve::True<Type>());
  TTS_EQUAL(eve::logical_ornot(Type{2}, Type{0}), eve::False<Type>());
}

TTS_CASE("Check eve::logical_ornot behavior on logicals")
{
  TTS_EQUAL(eve::logical_ornot(eve::False<Type>(), eve::True<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::logical_ornot(eve::True<Type>(), eve::False<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::logical_ornot(eve::True<Type>(), eve::True<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::logical_ornot(eve::False<Type>(), eve::False<Type>()), eve::True<Type>());
}

#endif
