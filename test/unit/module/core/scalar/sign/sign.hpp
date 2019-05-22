//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SIGN_HPP
#define SIGN_HPP

#include "test.hpp"
#include <eve/function/scalar/sign.hpp>
#include <eve/constant/smallestposval.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check sign return type")
{
  TTS_EXPR_IS(eve::sign(Type()),  Type);
}

TTS_CASE("Check eve::sign behavior")
{
  TTS_EQUAL(eve::sign(Type{0}), Type(0));
  TTS_EQUAL(eve::sign(Type{2}), Type(1));
  if constexpr(std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::sign(static_cast<Type>(-2)), Type(-1));
  }
}

#endif
