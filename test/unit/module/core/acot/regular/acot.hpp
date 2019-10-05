//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACOT_HPP
#define ACOT_HPP

#include <eve/function/acot.hpp>
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
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check acot return type")
{
  TTS_EXPR_IS(eve::acot(Type(0)),  Type);
}

TTS_CASE("Check eve::acot behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acot(eve::Nan<Type>()),   eve::Nan<Type>(), 0);
  }
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acot(eve::Inf<Type>()), 0, 0);
    TTS_ULP_EQUAL(eve::acot(eve::Minf<Type>()), 0, 0);
  }
  TTS_ULP_EQUAL(eve::acot(eve::Half<Type>()),   Type(1.107148717794090e+00), 1);
  TTS_ULP_EQUAL(eve::acot(eve::Mhalf<Type>()),  Type(-1.107148717794090e+00), 1);
  TTS_ULP_EQUAL(eve::acot(eve::Mone<Type>()),   -eve::Pio_4<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::acot(eve::One<Type>()),    eve::Pio_4<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::acot(eve::Zero<Type>()),   eve::Pio_2<Type>(), 1);
  TTS_ULP_EQUAL(eve::acot(eve::Mzero<Type>()),  -eve::Pio_2<Type>(), 1);
  TTS_ULP_EQUAL(eve::acot(eve::rec(eve::Smallestposval<Type>())), eve::Smallestposval<Type>(), 0.5);
}
#endif
