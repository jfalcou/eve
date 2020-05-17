//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acscd.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::acscd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acscd(T(0)), T);
}

TTS_CASE_TPL("Check eve::acscd behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acscd(T(0))  , eve::Nan<T>(), 1);
    TTS_ULP_EQUAL(eve::acscd(T(-0.)), eve::Nan<T>(), 1);
    TTS_IEEE_EQUAL(eve::acscd(eve::Nan<T>()) , (eve::Nan<T>()) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::acscd(eve::Inf<T>())  , (T(0)) );
    TTS_IEEE_EQUAL(eve::acscd(eve::Minf<T>()) , (T(0)) );
  }

  TTS_ULP_EQUAL(eve::acscd(T(-2.)),  -T(30), 1  );
  TTS_ULP_EQUAL(eve::acscd(T( 2.)),   T(30), 1  );
  TTS_ULP_EQUAL(eve::acscd(T(-1.)),  -T(90), 0.5);
  TTS_ULP_EQUAL(eve::acscd(T( 1.)),   T(90), 0.5);
}
