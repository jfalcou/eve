
//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/manhattan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::manhattan return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::manhattan(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::manhattan behavior", EVE_TYPE)
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::manhattan(eve::nan(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::manhattan(eve::inf(eve::as<T>()), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::manhattan(eve::valmax(eve::as<T>()), T(0))             , eve::valmax(eve::as<T>()));
  TTS_IEEE_EQUAL(eve::manhattan(T(0)            , eve::valmax(eve::as<T>())) , eve::valmax(eve::as<T>()));

  TTS_IEEE_EQUAL(eve::manhattan(T(-1), T(-1)), T(2));
  TTS_IEEE_EQUAL(eve::manhattan(T( 1), T( 1)), T(2));
  TTS_IEEE_EQUAL(eve::manhattan(T( 0), T( 0)), T(0));
  TTS_ULP_EQUAL(eve::manhattan(eve::sqrt_2(eve::as<T>()) , eve::sqrt_2(eve::as<T>())) , T(2)* eve::sqrt_2(eve::as<T>()), 0.5);
}

TTS_CASE_TPL("Check 3 params eve::manhattan behavior", EVE_TYPE)
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::manhattan(eve::nan(eve::as<T>()), eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve::manhattan(eve::inf(eve::as<T>()), eve::nan(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  TTS_ULP_EQUAL(eve::manhattan(eve::valmax(eve::as<T>()), T(0),              T(0)), eve::valmax(eve::as<T>()), 0);
  TTS_ULP_EQUAL(eve::manhattan(T(0)          , (eve::valmax(eve::as<T>())),  T(0)), eve::valmax(eve::as<T>()), 0);

  TTS_ULP_EQUAL(eve::manhattan(T(-1), T(-1), T(-1)), T(3) , 0);
  TTS_ULP_EQUAL(eve::manhattan(T( 1), T( 1), T(-1)), T(3) , 0);
  TTS_ULP_EQUAL(eve::manhattan(T( 0), T( 0), T( 0)), T(0) , 0);
  TTS_ULP_EQUAL(eve::manhattan(T( 1), T( 1), T( 1)), T(3) , 0);
}
