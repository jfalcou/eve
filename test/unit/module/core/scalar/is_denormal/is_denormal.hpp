//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_DENORMAL_HPP
#define IS_DENORMAL_HPP

#include <eve/function/scalar/is_denormal.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/false.hpp>
#include <eve/as_logical.hpp>

TTS_CASE("Check is_denormal return type")
{
  TTS_EXPR_IS(eve::is_denormal(Type(0)),  eve::as_logical_t<Type>);
}

TTS_CASE("Check eve::is_denormal behavior")
{
  TTS_EQUAL(eve::is_denormal(Type{0}), eve::False<Type>());
  TTS_EQUAL(eve::is_denormal(Type{2}), eve::False<Type>());
  TTS_EQUAL ( eve::is_denormal(eve::Smallestposval<Type>()/2)
            , eve::logical<Type>(eve::platform::supports_denormals)
            );
}

#endif
