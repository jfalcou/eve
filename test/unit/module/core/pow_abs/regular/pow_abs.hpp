//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow_abs.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check pow_abs return type")
{
  TTS_EXPR_IS(eve::pow_abs(Type(0), Type(0)), (Type));
}

TTS_CASE("Check eve::pow_abs behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pow_abs(eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pow_abs(eve::Inf<Type>(), eve::Half<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pow_abs(eve::Inf<Type>(), eve::Mhalf<Type>()), eve::Zero<Type>(), 0);
    TTS_ULP_EQUAL(eve::pow_abs(eve::Inf<Type>(), eve::Zero<Type>()), eve::One<Type>(), 0);
    TTS_ULP_EQUAL(eve::pow_abs(eve::Minf<Type>(), eve::Minf<Type>()), eve::Zero<Type>(), 0);
    TTS_ULP_EQUAL(eve::pow_abs(eve::Nan<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::pow_abs(Type(2), eve::Inf<Type>()), eve::Inf<Type>(), 0); 
    TTS_ULP_EQUAL(eve::pow_abs(eve::Half<Type>(), eve::Inf<Type>()), eve::Zero<Type>(), 0); 
  }
  TTS_ULP_EQUAL(eve::pow_abs(eve::Mone<Type>(), eve::Mone<Type>()), eve::One<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(eve::One<Type>(), eve::One<Type>()), eve::One<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(eve::Zero<Type>(), eve::Zero<Type>()), eve::One<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(-1),Type(5)), Type(1), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(-1),Type(6)), Type(1), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(0.5), Type(0.25)), Type(0.840896415253715), 2);
  TTS_ULP_EQUAL(eve::pow_abs(Type(0.5), Type(0.25)), Type(std::pow(Value(0.5), Value(0.25))), 2);
}


TTS_CASE("pow_abs conformity")
{
  // specific values tests
  TTS_ULP_EQUAL(eve::pow_abs(Type(0), Type(-1)), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(0), Type(-2)), eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(1), eve::Nan<Type>()), eve::One<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(1), eve::Inf<Type>()), eve::One<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(eve::Inf<Type>(), Type(-2)),  eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(eve::Inf<Type>(), Type( 2)),  eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(0.5), eve::Inf<Type>()),  eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(2), eve::Inf<Type>()),  eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(0.5), eve::Minf<Type>()),  eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(Type(2), eve::Minf<Type>()),  eve::Zero<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(eve::Nan<Type>(), Type(0)),  eve::One<Type>(), 0);
  TTS_ULP_EQUAL(eve::pow_abs(eve::Nan<Type>(), -Type(0)),  eve::One<Type>(), 0);

}
