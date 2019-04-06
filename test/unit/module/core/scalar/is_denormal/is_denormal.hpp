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

#include "test.hpp"
#include <eve/function/scalar/is_denormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check is_denormal return type")
{
  TTS_EXPR_IS(eve::is_denormal(Type(0))               , eve::logical<Type>);
  TTS_EXPR_IS(eve::is_denormal(eve::logical<Type>(0)) , eve::logical<Type>);
}

TTS_CASE("Check eve::is_denormal behavior")
{
  TTS_EXPECT_NOT( eve::is_denormal(Type{0})  );
  TTS_EXPECT_NOT( eve::is_denormal(Type{2}) );

  if constexpr(eve::platform::supports_denormals && std::is_floating_point_v<Type> )
    TTS_EXPECT( eve::is_denormal(eve::Smallestposval<Type>()/2));
  else
    TTS_EXPECT_NOT( eve::is_denormal(eve::Smallestposval<Type>()/2) );
}

#endif
