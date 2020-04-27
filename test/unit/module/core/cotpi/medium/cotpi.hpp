//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotpi.hpp>
#include <eve/function/sin.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/next.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::cotpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cotpi(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::cotpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(eve::Minf<T>()), (eve::Nan<T>()) );
  }
  TTS_ULP_EQUAL(eve::medium_(eve::cotpi)(T(1)), eve::Nan<T>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cotpi)(T(-1)),eve::Nan<T>(), 0.5);
  TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(T(0)), (eve::Inf<T>()));
  TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(T(-0.)), (eve::Minf<T>()));
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(T(22.5))), (T(0)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(-T(22.5))),(T(0)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(T(100000.0))), eve::Nan<T>(), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(T(-100000.0))),eve::Nan<T>(), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(T(100000000.0))), eve::Nan<T>(), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(T(-100000000.0))),eve::Nan<T>(), 0.5);
}

