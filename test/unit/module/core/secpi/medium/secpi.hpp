//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::secpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::secpi(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::secpi behavior", EVE_TYPE)
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(eve::Minf<T>()), (eve::Nan<T>()) );
  }
  TTS_ULP_EQUAL(eve::medium_(eve::secpi)(T(1)), (T(-1)), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::secpi)(T(-1)),(T(-1)), 0.5);
  TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(T(0)),(T(1)));
  TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(T(-0.)), (T(1)));
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(T(22.5))), (eve::Nan<T>()), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(-T(22.5))),(eve::Nan<T>()), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(T(100000.0))), T(1), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(T(-100000.0))),T(1), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(T(1000001.0))), T(-1), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(T(-100001.0))),T(-1), 0.5);
}
