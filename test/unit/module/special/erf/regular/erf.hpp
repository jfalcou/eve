//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/erf.hpp>
#include <eve/constant/halfeps.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::erf return type")
{
  TTS_EXPR_IS(eve::erf(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::erf behavior")
{
  auto eve__erf = [](auto x) { return eve::erf(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__erf(eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE(-1), 0);
    TTS_ULP_EQUAL(eve__erf(eve::inf(eve::as<EVE_TYPE>())), EVE_TYPE(1), 0);
    TTS_ULP_EQUAL(eve__erf(eve::nan(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(-0.0)), EVE_TYPE(0), 0);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(1)), EVE_TYPE(0.842700792949714869341220635083), 0.5);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(2)), EVE_TYPE(0.995322265018952734162069256367), 0);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(0)), EVE_TYPE(0), 0);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(5)), EVE_TYPE(0.99999999999846254020557196515), 0);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(27)), EVE_TYPE(1), 0);

  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(-1)), EVE_TYPE(-0.842700792949714869341220635083), 0.5);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(-2)), EVE_TYPE(-0.995322265018952734162069256367), 0);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(-5)), EVE_TYPE(-0.99999999999846254020557196515), 0);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(-27)), EVE_TYPE(-1), 0);

  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(0.5)), EVE_TYPE(0.520499877813046537682746653892), 0.5);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(0.1)), EVE_TYPE(0.112462916018284892203275071744), 0);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(0.5)), EVE_TYPE(0.520499877813046537682746653892), 0.5);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(-0.5)), EVE_TYPE(-0.520499877813046537682746653892), 0.5);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(-0.1)), EVE_TYPE(-0.112462916018284892203275071744), 0);
  TTS_ULP_EQUAL(eve__erf( eve::halfeps(eve::as<EVE_TYPE>())),  eve::eps(eve::as<EVE_TYPE>())*eve::rsqrt(eve::pi(eve::as<EVE_TYPE>())), 0);
  TTS_ULP_EQUAL(eve__erf(-eve::halfeps(eve::as<EVE_TYPE>())), -eve::eps(eve::as<EVE_TYPE>())*eve::rsqrt(eve::pi(eve::as<EVE_TYPE>() )), 0);
  TTS_ULP_EQUAL(eve__erf(EVE_TYPE(20)), EVE_TYPE(1), 0);
}
