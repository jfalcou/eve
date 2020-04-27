//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cospi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::cospi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cospi(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::cospi behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T> )
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_IEEE_EQUAL((eve::cospi)(eve::Nan<T>()) , (eve::Nan<T>()) );
      TTS_IEEE_EQUAL((eve::cospi)(eve::Inf<T>()) , (eve::Nan<T>()) );
      TTS_IEEE_EQUAL((eve::cospi)(eve::Minf<T>()), (eve::Nan<T>()) );
    }
    TTS_ULP_EQUAL((eve::cospi)(T(1)), T(-1), 0.5);
    TTS_ULP_EQUAL((eve::cospi)(T(-1)),T(-1), 0.5);
    TTS_IEEE_EQUAL((eve::cospi)(T(0)), (T(1)));
    TTS_IEEE_EQUAL((eve::cospi)(T(-0.)), (T(1)));
    TTS_ULP_EQUAL(((eve::cospi)(T(22.5))), (T(0)), 0.5);
    TTS_ULP_EQUAL(((eve::cospi)(-T(22.5))),(T(0)), 0.5);
    TTS_ULP_EQUAL(((eve::cospi)(T(100000.0))), T(1), 0.5);
    TTS_ULP_EQUAL(((eve::cospi)(T(-100000.0))),T(1), 0.5);
    TTS_ULP_EQUAL(((eve::cospi)(T(100000000.0))), T(1), 0.5);
    TTS_ULP_EQUAL(((eve::cospi)(T(-100000000.0))),T(1), 0.5);
    TTS_ULP_EQUAL(((eve::cospi)(T(eve::Valmax<T>()))),T(1), 0.5);
    TTS_ULP_EQUAL(((eve::cospi)(T(eve::Valmax<T>()/10))),T(1), 0.5);
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL((eve::cospi)(T(1)), (T(-1)));
    TTS_EQUAL((eve::cospi)(T(-1)),(T(-1)));
    TTS_EQUAL((eve::cospi)(T(2)), (T(1)));
    TTS_EQUAL((eve::cospi)(T(-2)), (T(1)));
  }
}

