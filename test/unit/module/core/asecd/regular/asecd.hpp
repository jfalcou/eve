//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ASECD_HPP
#define ASECD_HPP

#include <eve/function/asecd.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/smallestposval.hpp>
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

TTS_CASE("Check asecd return type")
{
  TTS_EXPR_IS(eve::asecd(Type(0)),  Type);
}

TTS_CASE("Check eve::asecd behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asecd(eve::Inf<Type>()),     Type(90), 0);
    TTS_ULP_EQUAL(eve::asecd(eve::Minf<Type>()),    Type(90), 0);
  }
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asecd(eve::Nan<Type>()),     eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::asecd(eve::Zero<Type>()),    eve::Nan<Type>(), 1);
    TTS_ULP_EQUAL(eve::asecd(eve::Mzero<Type>()),   eve::Nan<Type>(), 1);
  }
  TTS_ULP_EQUAL(eve::asecd(Type(-2)),             2*Type(180)/3, 1);
  TTS_ULP_EQUAL(eve::asecd(Type(2)),              Type(180)/3, 1);
  TTS_ULP_EQUAL(eve::asecd(eve::Mone<Type>()),    Type(180), 0.5);
  TTS_ULP_EQUAL(eve::asecd(eve::One<Type>()),     eve::Zero<Type>(), 0.5);
}

#endif
