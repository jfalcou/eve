//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITOFSIGN_HPP
#define BITOFSIGN_HPP

#include "test.hpp"
#include <eve/function/scalar/bitofsign.hpp>
#include <eve/constant/signmask.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check bitofsign return type") { TTS_EXPR_IS(eve::bitofsign(Type()), Type); }

TTS_CASE("Check eve::bitofsign behavior")
{
  TTS_EQUAL(eve::bitofsign(Type{0}), Type(0));
  TTS_EQUAL(eve::bitofsign(Type{2}), Type(0));
  if constexpr(std::is_signed_v<Type>)
  { TTS_EQUAL(eve::bitofsign(static_cast<Type>(-2)), eve::Signmask<Type>()); }
}

#endif
