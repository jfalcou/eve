//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SQRT_HPP
#define SQRT_HPP

#include <eve/function/scalar/sqrt.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <type_traits>

TTS_CASE("Check sqrt return type") { TTS_EXPR_IS(eve::sqrt(Type(0)), Type); }

TTS_CASE("Check eve::sqrt behavior")
{
  TTS_EQUAL(eve::sqrt(Type{1}), Type(1));
  TTS_EQUAL(eve::sqrt(Type{4}), Type(2));

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::sqrt(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::sqrt(-eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::sqrt(eve::Mzero<Type>()), Type(0));
    TTS_EQUAL(eve::sqrt(eve::Zero<Type>()), Type(0));
    TTS_ULP_EQUAL(eve::sqrt(Type(2)), eve::Sqrt_2<Type>(), 0.5);
  }
}

TTS_CASE("Check eve::raw_(eve::sqrt) behavior")
{
  TTS_EQUAL(eve::raw_(eve::sqrt)(Type{1}), Type(1));
  TTS_EQUAL(eve::raw_(eve::sqrt)(Type{4}), Type(2));

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::raw_(eve::sqrt)(eve::Nan<Type>()), eve::Nan<Type>());
    TTS_IEEE_EQUAL(eve::raw_(eve::sqrt)(-eve::Nan<Type>()), eve::Nan<Type>());
    TTS_EQUAL(eve::raw_(eve::sqrt)(eve::Mzero<Type>()), Type(0));
    TTS_EQUAL(eve::raw_(eve::sqrt)(eve::Zero<Type>()), Type(0));
    TTS_ULP_EQUAL(eve::raw_(eve::sqrt)(Type(2)), eve::Sqrt_2<Type>(), 0.5);
  }
}

#endif
