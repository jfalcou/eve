//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
  TTS_EXPR_IS(eve::raw_(eve::pow_abs)(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::raw_(eve::pow_abs) behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Inf<EVE_TYPE>(), eve::Half<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Inf<EVE_TYPE>(), eve::Mhalf<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Minf<EVE_TYPE>(), eve::Minf<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(2), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0); 
    TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Half<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0); 
  }
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Mone<EVE_TYPE>(), eve::Mone<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::One<EVE_TYPE>(), eve::One<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(-1),EVE_TYPE(5)), EVE_TYPE(1), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(-1),EVE_TYPE(6)), EVE_TYPE(1), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(0.5), EVE_TYPE(0.25)), EVE_TYPE(0.840896415253715), 2);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(0.5), EVE_TYPE(0.25)), EVE_TYPE(std::pow(EVE_VALUE(0.5), EVE_VALUE(0.25))), 2);
}


TTS_CASE(" eve::raw_(eve::pow_abs) conformity")
{
  // conform to std::pow(abs(a), b)
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(0), EVE_TYPE(-1)), eve::Inf<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(0), EVE_TYPE(-2)), eve::Inf<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Inf<EVE_TYPE>(), EVE_TYPE(-2)),  eve::Zero<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Inf<EVE_TYPE>(), EVE_TYPE( 2)),  eve::Inf<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(0.5), eve::Inf<EVE_TYPE>()),  eve::Zero<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(2), eve::Inf<EVE_TYPE>()),  eve::Inf<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(0.5), eve::Minf<EVE_TYPE>()),  eve::Inf<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(2), eve::Minf<EVE_TYPE>()),  eve::Zero<EVE_TYPE>(), 0);
  // non conform
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(1), eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(EVE_TYPE(1), eve::Inf<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Nan<EVE_TYPE>(), EVE_TYPE(0)),  eve::Nan<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Nan<EVE_TYPE>(), -EVE_TYPE(0)),  eve::Nan<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Inf<EVE_TYPE>(), eve::Zero<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
  TTS_ULP_EQUAL(eve::raw_(eve::pow_abs)(eve::Zero<EVE_TYPE>(), eve::Zero<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
}
 
