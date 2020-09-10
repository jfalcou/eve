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
#include <eve/function/rec.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_even.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::cotpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cotpi(T()), T);
}

TTS_CASE_TPL("Check eve::eve::cotpi behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cotpi(eve::nan(eve::as<T>()) ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::cotpi(eve::inf(eve::as<T>()) ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::cotpi(eve::Minf<T>()) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::cotpi(T( 0 )), eve::inf(eve::as<T>())  );
  TTS_IEEE_EQUAL(eve::cotpi(T(-0.)), eve::Minf<T>() );

  TTS_ULP_EQUAL(eve::cotpi( T(1)          ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::cotpi(-T(1)          ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::cotpi( T(22.5)       ) , T(0)          , 0.5);
  TTS_ULP_EQUAL(eve::cotpi(-T(22.5)       ) , T(0)          , 0.5);
  TTS_ULP_EQUAL(eve::cotpi( T(100000.0)   ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::cotpi(-T(100000.0)   ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::cotpi( T(100000000.0)) , eve::nan(eve::as<T>()) , 0.5);

  TTS_ULP_EQUAL(eve::cotpi( T(eve::Valmax<T>()) )   , eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve::cotpi( T(eve::Valmax<T>())/10) , eve::nan(eve::as<T>()), 0.5);
}
