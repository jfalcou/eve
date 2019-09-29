//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ATAN2_HPP
#define ATAN2_HPP

#include <eve/function/scalar/atan2.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>  
#include <eve/constant/mzero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp> 
#include <eve/constant/zero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>   
#include <eve/constant/pi.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>


TTS_CASE("Check atan2 return type")
{
  TTS_EXPR_IS(eve::atan2(Type(0), Type(0)),  Type);
}

TTS_CASE("Check eve::pedantic_(eve::atan2) behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::atan2(eve::Inf<Type>(),eve::One<Type>()),     eve::Pio_2<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Inf<Type>(),eve::Mone<Type>()),    eve::Pio_2<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Minf<Type>(),eve::One<Type>()),   -eve::Pio_2<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Minf<Type>(),eve::Mone<Type>()),  -eve::Pio_2<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::One<Type>(), eve::Minf<Type>()),   eve::Pi<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Mone<Type>(), eve::Minf<Type>()), -eve::Pi<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::One<Type>(), eve::Inf<Type>()),    eve::Zero<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Mone<Type>(), eve::Inf<Type>()),  -eve::Zero<Type>(), 0.5);
    TTS_EXPECT(eve::is_negative(eve::atan2(eve::Mone<Type>(),        eve::Inf<Type>())));
    TTS_EXPECT(eve::is_positive(eve::atan2(eve::One<Type>(),         eve::Inf<Type>())));
    TTS_ULP_EQUAL(eve::atan2(eve::Inf<Type>(),eve::One<Type>()),     eve::Pio_2<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Minf<Type>(),eve::One<Type>()),   -eve::Pio_2<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::One<Type>(),eve::Inf<Type>()),     eve::Zero<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::One<Type>(),eve::Minf<Type>()),    eve::Pi<Type>(), 0.5);
  }
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan2(eve::Nan<Type>(), eve::Nan<Type>()),     eve::Nan<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Nan<Type>(), eve::Zero<Type>()),    eve::Nan<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Zero<Type>(), eve::Nan<Type>()),    eve::Nan<Type>(), 0.5);
  }
  TTS_ULP_EQUAL(eve::atan2(eve::Half<Type>(), eve::Half<Type>()),     eve::Pio_4<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::Mhalf<Type>(), eve::Mhalf<Type>()),  -Type(3)*eve::Pio_4<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::Mone<Type>(), eve::Mone<Type>()),    -Type(3)*eve::Pio_4<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::One<Type>(), eve::One<Type>()),       eve::Pio_4<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::Mzero<Type>(), eve::Mone<Type>()),   -eve::Pi<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::Zero<Type>(), eve::Mone<Type>()),     eve::Pi<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::Mone<Type>(), eve::Mzero<Type>()),   -eve::Pio_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::Mone<Type>(), eve::Zero<Type>()),    -eve::Pio_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::One<Type>(), eve::Mzero<Type>()),     eve::Pio_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2(eve::One<Type>(), eve::Zero<Type>()),      eve::Pio_2<Type>(), 0.5);

}
#endif
