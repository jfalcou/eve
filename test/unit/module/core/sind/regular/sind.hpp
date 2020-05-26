//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sind.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::sind return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sind(T()), T);
}

TTS_CASE_TPL("Check eve::sind behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sind(eve::Nan<T>() ) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::sind(eve::Inf<T>() ) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::sind(eve::Minf<T>()) , eve::Nan<T>() );
  }

  TTS_IEEE_EQUAL(eve::sind(T( 0 )), T(0) );
  TTS_IEEE_EQUAL(eve::sind(T(-0.)), T(0) );
  TTS_ULP_EQUAL(eve::sind( T(1)    ) , T(1.745240643728351281941897851631619247225272030714e-2)  , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(1)    ) , T(-1.745240643728351281941897851631619247225272030714e-2) , 4.0);
  TTS_ULP_EQUAL(eve::sind( T(45.0) ) , T(0.70710678118654752440084436210484903928483593768847)   , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(45.0) ) , T(-0.70710678118654752440084436210484903928483593768847)  , 4.0);
  TTS_ULP_EQUAL(eve::sind( T(500.0)) , T(0.64278760968653932632264340990726343290755988420567)   , 4.0);
  TTS_ULP_EQUAL(eve::sind(-T(500.0)) , T(-0.64278760968653932632264340990726343290755988420567)  , 4.0);
}
