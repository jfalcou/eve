//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ASEC_HPP
#define ASEC_HPP

#include <eve/function/asec.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check asec return type")
{
  TTS_EXPR_IS(eve::asec(Type(0)),  Type);
}

TTS_CASE("Check eve::asec behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asec(eve::Inf<Type>()),     eve::Pio_2<Type>(), 0);
    TTS_ULP_EQUAL(eve::asec(eve::Minf<Type>()),    eve::Pio_2<Type>(), 0);
  }
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asec(eve::Nan<Type>()),     eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::asec(eve::Zero<Type>()),    eve::Nan<Type>(), 1);
    TTS_ULP_EQUAL(eve::asec(eve::Mzero<Type>()),   eve::Nan<Type>(), 1);
  }
  TTS_ULP_EQUAL(eve::asec(Type(-2)),             2*eve::Pi<Type>()/3, 1);
  TTS_ULP_EQUAL(eve::asec(Type(2)),              eve::Pi<Type>()/3, 1);
  TTS_ULP_EQUAL(eve::asec(eve::Mone<Type>()),    eve::Pi<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::asec(eve::One<Type>()),     eve::Zero<Type>(), 0.5);
}

#endif
