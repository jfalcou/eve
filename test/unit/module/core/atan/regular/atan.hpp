//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ATAN_HPP
#define ATAN_HPP

#include <eve/function/atan.hpp>
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
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check atan return type")
{
  TTS_EXPR_IS(eve::atan(Type(0)),  Type);
}

TTS_CASE("Check eve::eve::atan behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan(eve::Nan<Type>()), eve::Nan<Type>(), 0);
  }
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::atan(eve::Inf<Type>()),   eve::Pio_2<Type>(), 0);
    TTS_ULP_EQUAL(eve::atan(eve::Minf<Type>()), -eve::Pio_2<Type>(), 0);
  }
  TTS_ULP_EQUAL(eve::atan(eve::Half<Type>()),  Type(4.636476090008061e-01),  0.5);
  TTS_ULP_EQUAL(eve::atan(eve::Mhalf<Type>()), Type(-4.636476090008061e-01), 0.5);
  TTS_ULP_EQUAL(eve::atan(eve::Mone<Type>()),  -eve::Pio_4<Type>(),       0.5);
  TTS_ULP_EQUAL(eve::atan(eve::One<Type>()),    eve::Pio_4<Type>(),       0.5);
  TTS_ULP_EQUAL(eve::atan(eve::Zero<Type>()),   eve::Zero<Type>(),        0.5);
  TTS_EXPECT(eve::is_negative(eve::atan(eve::Mzero<Type>())));
  TTS_EXPECT(eve::is_positive(eve::atan(eve::Zero<Type>())));
}


#endif
