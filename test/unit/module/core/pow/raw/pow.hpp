//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/pow.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
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
#include <tts/tests/basic.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::raw_(eve::pow) return type")
{
  TTS_EXPR_IS(eve::raw_(eve::pow)(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE));
}


TTS_CASE("pow conformity")
{
  if (std::is_floating_point_v<EVE_VALUE>)
  {
    // std::pow conform
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(EVE_TYPE(0), EVE_TYPE(-1)), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-EVE_TYPE(0), EVE_TYPE(-2)), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(EVE_TYPE(0), EVE_TYPE(-2)), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(EVE_TYPE(0),  eve::Minf<EVE_TYPE>()),  eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-EVE_TYPE(0),  eve::Minf<EVE_TYPE>()),  eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(EVE_TYPE(0.5), eve::Inf<EVE_TYPE>()),  eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(EVE_TYPE(2), eve::Inf<EVE_TYPE>()),  eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(EVE_TYPE(0.5), eve::Minf<EVE_TYPE>()),  eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(EVE_TYPE(2), eve::Minf<EVE_TYPE>()),  eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<EVE_TYPE>(), EVE_TYPE(4) ),  eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<EVE_TYPE>(), EVE_TYPE(-4) ),  eve::Zero<EVE_TYPE>(), 0);
  }
  TTS_ULP_EQUAL(0, 0, 0);
}
