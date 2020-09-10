//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/stirling.hpp>
#include <eve/function/round.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::stirling return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::stirling(T()), T);
}

TTS_CASE_TPL("Check eve::stirling behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::stirling(eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::stirling(eve::Minf<T>() ) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::stirling(eve::Mone<T>() ) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::stirling(eve::nan(eve::as<T>())  ) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::round(eve::stirling(T(1))), T(1), 0.5);
  TTS_ULP_EQUAL(eve::round(eve::stirling(T(2))), T(1), 0.5);
}
