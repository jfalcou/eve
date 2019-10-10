//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check asin return type")
{
  TTS_EXPR_IS(eve::asin(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::asin behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asin(eve::Nan<Type>()) , eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::asin(Type(2))          , eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::asin(Type(-2))         , eve::Nan<Type>(), 0);
  }

  TTS_ULP_EQUAL(eve::asin(eve::Half<Type>()),    eve::Pio_2<Type>()/3, 0.5);
  TTS_ULP_EQUAL(eve::asin(eve::Mhalf<Type>()),   -eve::Pio_2<Type>()/3, 0.5);
  TTS_ULP_EQUAL(eve::asin(eve::Mone<Type>()),    -eve::Pio_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::asin(eve::One<Type>()),     eve::Pio_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::asin(eve::Zero<Type>()),    eve::Zero<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::asin(eve::Mzero<Type>()),   eve::Zero<Type>(), 0.5);
  // TTS_EXPECT(eve::is_negative(eve::asin(eve::Mzero<Type>())));
  // TTS_EXPECT(eve::is_positive(eve::asin(eve::Zero<Type>())));
}
