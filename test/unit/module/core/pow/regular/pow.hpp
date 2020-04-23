//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/half.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/pow.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/basic.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check pow_abs return type")
{
  if( std::is_floating_point_v<EVE_VALUE> )
  {
    TTS_EXPR_IS(eve::pow(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE));
  }
  TTS_EXPR_IS(eve::pow(EVE_TYPE(0), int(0)), (EVE_TYPE));
}

TTS_CASE("pow conformity")
{
  if constexpr( std::is_floating_point_v<EVE_VALUE> )
  {
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(0), EVE_TYPE(-1)), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(0), EVE_TYPE(-1)), eve::Minf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(0), EVE_TYPE(-2)), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(0), EVE_TYPE(-2)), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(0), eve::Minf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(0), eve::Minf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(1), eve::Minf<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(1), eve::Inf<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(1), eve::Nan<EVE_TYPE>()), eve::One<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(eve::Nan<EVE_TYPE>(), EVE_TYPE(0)), eve::One<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(eve::Nan<EVE_TYPE>(), -EVE_TYPE(0)), eve::One<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(0.5), eve::Inf<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(2), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(0.5), eve::Minf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(2), eve::Minf<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(0.5), eve::Inf<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(2), eve::Inf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(0.5), eve::Minf<EVE_TYPE>()), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(-EVE_TYPE(2), eve::Minf<EVE_TYPE>()), eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(eve::Minf<EVE_TYPE>(), EVE_TYPE(-3)), eve::Mzero<EVE_TYPE>(), 0);
    TTS_EXPECT(eve::all(eve::is_negative(eve::pow(eve::Minf<EVE_TYPE>(), EVE_TYPE(-3)))));
    TTS_ULP_EQUAL(eve::pow(eve::Minf<EVE_TYPE>(), EVE_TYPE(-4)), eve::Zero<EVE_TYPE>(), 0);
    TTS_EXPECT(eve::all(eve::is_positive(eve::pow(eve::Minf<EVE_TYPE>(), EVE_TYPE(-4)))));
    TTS_ULP_EQUAL(eve::pow(eve::Inf<EVE_TYPE>(), EVE_TYPE(4)), eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(eve::Inf<EVE_TYPE>(), EVE_TYPE(-4)), eve::Zero<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(2), EVE_TYPE(-3)), (EVE_TYPE(1 / 8.0)), 0);
    TTS_ULP_EQUAL(eve::pow(EVE_TYPE(2), EVE_TYPE(3)), (EVE_TYPE(8)), 0);
  }

  TTS_ULP_EQUAL(eve::pow(EVE_TYPE(2), -3), (EVE_TYPE(1 / 8.0)), 0);
  TTS_ULP_EQUAL(eve::pow(EVE_TYPE(2), 3), (EVE_TYPE(8)), 0);
  TTS_ULP_EQUAL(eve::pow(EVE_TYPE(2), 3u), (EVE_TYPE(8)), 0);
}
