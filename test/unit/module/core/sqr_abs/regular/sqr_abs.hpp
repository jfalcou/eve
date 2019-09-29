//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SQR_ABS_HPP
#define SQR_ABS_HPP

#include <eve/function/scalar/sqr_abs.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/inc.hpp>
#include <eve/as_logical.hpp>
#include <type_traits>

TTS_CASE("Check sqr_abs return type") { TTS_EXPR_IS(eve::sqr_abs(Type(0)), Type); }

TTS_CASE("Check eve::sqr_abs behavior")
{
  TTS_EQUAL(eve::sqr_abs(Type{1}), Type(1));
  TTS_EQUAL(eve::sqr_abs(Type{2}), Type(4));
  
  TTS_EQUAL(eve::sqr_abs(static_cast<Type>(-2)), Type(4));
  TTS_EQUAL(eve::sqr_abs(eve::Mzero<Type>()), Type(0));
  TTS_EQUAL(eve::sqr_abs(eve::Zero<Type>()), Type(0));
}

#endif

