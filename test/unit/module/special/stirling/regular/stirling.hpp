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

TTS_CASE_TPL("Check eve::stirling return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::stirling(T()), T);
}

TTS_CASE_TPL("Check eve::stirling behavior", EVE_TYPE)
{
  auto eve__stirling =  [](auto x) { return eve::stirling(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__stirling(eve::inf(eve::as<T>())  ) , eve::inf(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve__stirling(eve::minf(eve::as<T>()) ) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve__stirling(eve::mone(eve::as<T>()) ) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve__stirling(eve::nan(eve::as<T>())  ) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::round(eve__stirling(T(1))), T(1), 0.5);
  TTS_ULP_EQUAL(eve::round(eve__stirling(T(2))), T(1), 0.5);
}
