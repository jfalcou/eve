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
#include <eve/function/cos.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted_(eve::cotpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::cotpi)(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::cotpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(eve::Inf<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(eve::Minf<T>()), (eve::Nan<T>()) );
  }
  TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(T(0)), (eve::Inf<T>()));
  TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(T(-0.)), (eve::Minf<T>()));
  TTS_ULP_EQUAL((eve::restricted_(eve::cotpi)(T(0.125))), (T(2.414213562373095048801688724209698078569671875377)), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::cotpi)(T(-0.125))), (T(-2.414213562373095048801688724209698078569671875377)), 0.5);
}
