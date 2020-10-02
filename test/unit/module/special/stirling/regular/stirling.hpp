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

TTS_CASE("Check eve::stirling return type")
{
  TTS_EXPR_IS(eve::stirling(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::stirling behavior")
{
  auto eve__stirling =  [](auto x) { return eve::stirling(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__stirling(eve::inf(eve::as<EVE_TYPE>())  ) , eve::inf(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve__stirling(eve::minf(eve::as<EVE_TYPE>()) ) , eve::nan(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve__stirling(eve::mone(eve::as<EVE_TYPE>()) ) , eve::nan(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve__stirling(eve::nan(eve::as<EVE_TYPE>())  ) , eve::nan(eve::as<EVE_TYPE>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::round(eve__stirling(EVE_TYPE(1))), EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL(eve::round(eve__stirling(EVE_TYPE(2))), EVE_TYPE(1), 0.5);
}
