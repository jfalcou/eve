//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/radindeg.hpp>

#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::radindeg return type") { TTS_EXPR_IS(eve::radindeg(EVE_TYPE(0)), (EVE_TYPE)); }

TTS_CASE("Check eve::radindeg behavior")
{
  TTS_ULP_EQUAL(eve::radindeg(-eve::Pi<EVE_TYPE>()), (EVE_TYPE(-180)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg(-eve::Pio_2<EVE_TYPE>()), (EVE_TYPE(-90)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg(-eve::Pio_4<EVE_TYPE>()), (EVE_TYPE(-45)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg((EVE_TYPE(0))), (EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg(eve::Pio_4<EVE_TYPE>()), (EVE_TYPE(45)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg(eve::Pio_2<EVE_TYPE>()), (EVE_TYPE(90)), 0.5);
  TTS_ULP_EQUAL(eve::radindeg(eve::Pi<EVE_TYPE>()), (EVE_TYPE(180)), 0.5);
}
