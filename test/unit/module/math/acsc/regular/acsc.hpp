//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acsc.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::acsc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acsc(T(0)), T);
}

TTS_CASE_TPL("Check eve::acsc behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acsc(T(0))   , eve::nan(eve::as<T>()), 1);
    TTS_ULP_EQUAL(eve::acsc(T(-0.)) , eve::nan(eve::as<T>()), 1);
    TTS_IEEE_EQUAL(eve::acsc(eve::nan(eve::as<T>()) ) , (eve::nan(eve::as<T>())) );
  }

  TTS_ULP_EQUAL(eve::acsc(T(-2.)), -eve::Pio_2<T>()/3 , 1   );
  TTS_ULP_EQUAL(eve::acsc(T( 2.)),  eve::Pio_2<T>()/3 , 1   );
  TTS_ULP_EQUAL(eve::acsc(T(-1.)), -eve::Pio_2<T>()   , 0.5 );
  TTS_ULP_EQUAL(eve::acsc(T( 1.)),  eve::Pio_2<T>()   , 0.5 );

  TTS_IEEE_EQUAL(eve::acsc(eve::inf(eve::as<T>())) , (T(0)));
  TTS_IEEE_EQUAL(eve::acsc(eve::minf(eve::as<T>())), (T(0)));
}
