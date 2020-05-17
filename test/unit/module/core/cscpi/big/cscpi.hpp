//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::big_(eve::cscpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big_(eve::cscpi)(T()), T);
}

TTS_CASE_TPL("Check eve::big_(eve::cscpi) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(eve::Nan<T>()) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(eve::Inf<T>()) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(eve::Minf<T>()), eve::Nan<T>() );
  }

  TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(T(0))  , eve::Inf<T>() );
  TTS_IEEE_EQUAL(eve::big_(eve::cscpi)(T(-0.)), eve::Minf<T>());

  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(-T(100000000.0) ) , eve::Nan<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(-T(100000.0)    ) , eve::Nan<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(-T(100000.5)    ) , T(-1)           , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)( T(1)           ) , eve::Nan<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(T(0.125)        ) , T(2.6131259297527530557132863468543743071675223766986)  , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(-T(0.125)       ) , T(-2.6131259297527530557132863468543743071675223766986) , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(-T(1)           ) , eve::Nan<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(-T(22.5)        ) , T(-1)           , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)(-T(22.25)       ) ,-eve::Sqrt_2<T>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)( T(22.25)       ) , eve::Sqrt_2<T>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)( T(22.5)        ) , T(1)            , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)( T(100000.0)    ) , eve::Nan<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)( T(100000.5)    ) , T(1)            , 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cscpi)( T(100000000.0) ) , eve::Nan<T>()   , 0.5);
}
