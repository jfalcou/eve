//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acot.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::acot return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acot(T(0)), T);
}

TTS_CASE_TPL("Check eve::acot behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acot(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acot(eve::inf(eve::as<T>())) , T(0), 0);
    TTS_ULP_EQUAL(eve::acot(eve::minf(eve::as<T>())), T(0), 0);
  }

  TTS_ULP_EQUAL(eve::acot(T( 0.5))         ,  T(1.107148717794090e+00)  , 1   );
  TTS_ULP_EQUAL(eve::acot(T(-0.5))         ,  T(-1.107148717794090e+00) , 1   );
  TTS_ULP_EQUAL(eve::acot(T(-1. ))         , -eve::pio_4(eve::as<T>())           , 0.5 );
  TTS_ULP_EQUAL(eve::acot(T( 1. ))         ,  eve::pio_4(eve::as<T>())           , 0.5 );
  TTS_ULP_EQUAL(eve::acot(T( 0. ))         ,  eve::pio_2(eve::as<T>())           , 1   );

  auto inv_smallest = eve::rec(eve::smallestposval(eve::as<T>()));
  TTS_ULP_EQUAL(eve::acot(T(-0.)) , -eve::pio_2(eve::as<T>())           , 1   );
  TTS_ULP_EQUAL(eve::acot(inv_smallest)       ,  eve::smallestposval(eve::as<T>())  , 0.5 );
}
