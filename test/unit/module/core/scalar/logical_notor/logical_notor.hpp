//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_NOTOR_HPP
#define LOGICAL_NOTOR_HPP

#include <eve/function/scalar/logical_notor.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp> 
#include <type_traits>

TTS_CASE( "Check logical_notor return type" )
{
  TTS_EXPR_IS(eve::logical_notor(Type(), Type()) ,  eve::as_logical_t<Type>);
  using l_t = eve::as_logical_t<Type>; 
  TTS_EXPR_IS(eve::logical_notor(l_t(), l_t()) ,  eve::as_logical_t<Type>);   
}

TTS_CASE("Check eve::logical_notor behavior")
{
  TTS_EQUAL(eve::logical_notor(Type{0}, Type{1}), eve::True<Type>());
  TTS_EQUAL(eve::logical_notor(Type{0}, Type{0}), eve::True<Type>());
  TTS_EQUAL(eve::logical_notor(Type{1}, Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::logical_notor(Type{2}, Type{1}), eve::True<Type>());
}

TTS_CASE("Check eve::logical_notor behavior on logicals")
{
  TTS_EQUAL(eve::logical_notor(eve::False<Type>(), eve::True<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::logical_notor(eve::False<Type>(), eve::False<Type>()), eve::True<Type>());
  TTS_EQUAL(eve::logical_notor(eve::True<Type>(), eve::False<Type>()), eve::False<Type>());
  TTS_EQUAL(eve::logical_notor(eve::True<Type>(), eve::True<Type>()), eve::True<Type>());
}

#endif
