//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gammainc.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::gammainc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::gammainc(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::gammainc behavior", EVE_TYPE)
{
  auto eve__gammainc =  [](auto x, auto y) { return eve::gammainc(x, y); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__gammainc(eve::nan(eve::as<T>()), T(1))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__gammainc(eve::inf(eve::as<T>()), T(1))  , T(1) );
  }

  TTS_ULP_EQUAL(eve__gammainc(T(0.0), T(1.0)), T(0), 0.5 );
  TTS_ULP_EQUAL(eve__gammainc(T(1.0), T(1.0)), eve::oneminus(eve::exp(T(-1))), 1);
  TTS_ULP_EQUAL(eve__gammainc(T(0.0), T(0.0)), T(1), 0.5 );
  TTS_ULP_EQUAL(eve__gammainc(T(0.25), T(1.0)), T(2.211992169285951e-01), 1 );
  TTS_ULP_EQUAL(eve__gammainc(T(0.25), T(0.25)), T(7.436779447314609e-01), 0.5 );
  TTS_ULP_EQUAL(eve__gammainc(T(1.0), T(0.25)), T(9.320788679898916e-01), 5.5 );
  TTS_ULP_EQUAL(eve__gammainc(T(0.25), T(2.0)), T(2.649902116074387e-02), 5.5 );
  TTS_ULP_EQUAL(eve__gammainc(T(0.25), T(2.25)), T( 1.460405690340118e-02), 0.5 );
  TTS_ULP_EQUAL(eve__gammainc(T(1.0), T(2.25)), T(2.015171022500710e-01), 5.5 );
  TTS_ULP_EQUAL(eve__gammainc(T(10.25), T(2.0)), T(9.993562658346851e-01), 2 );
  TTS_ULP_EQUAL(eve__gammainc(T(10.25), T(2.25)), T(9.991962820874968e-01), 0.5 );
  TTS_ULP_EQUAL(eve__gammainc(T(11.0), T(2.25)), T(9.996704204992496e-01), 5.5 );

}
