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

TTS_CASE_TPL("Check eve::raw_(eve::pow) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw_(eve::pow)(T(0), T(0)), T);
}

TTS_CASE_TPL("pow conformity", EVE_TYPE)
{
  if (eve::floating_value<T>)
  {
    // std::pow conform
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0), T(-1)), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(0), T(-2)), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0), T(-2)), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0),  eve::Minf<T>()),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(0),  eve::Minf<T>()),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0.5), eve::Inf<T>()),  T( 0 ), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(2), eve::Inf<T>()),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(0.5), eve::Minf<T>()),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(2), eve::Minf<T>()),  T( 0 ), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<T>(), T(4) ),  eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Inf<T>(), T(-4) ),  T( 0 ), 0);
    // std::pow non conform
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(0), T(-1)), eve::Inf<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(1),  eve::Minf<T>()),  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(1),  eve::Inf <T>()),  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(T(1), eve::Nan<T>()) ,  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Nan<T>(), T(0)) ,  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Nan<T>(), -T(0)) ,  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(0.5), eve::Inf<T>()),  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(2), eve::Inf<T>()),  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(0.5), eve::Minf<T>()),  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(-T(2), eve::Minf<T>()),  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<T>(), T(-3) ),  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<T>(), T(-4) ),  eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<T>(),  T(-4)), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::raw_(eve::pow)(eve::Minf<T>(), T(-4)) , eve::Nan<T>(), 0);
  }
  TTS_ULP_EQUAL(0, 0, 0);
}
