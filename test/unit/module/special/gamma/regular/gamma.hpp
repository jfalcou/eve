//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gamma.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::gamma return type")
{
  TTS_EXPR_IS(eve::gamma(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::gamma behavior")
{
  auto eve__gamma =  [](auto x) { return eve::gamma(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__gamma(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve__gamma(eve::inf(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve__gamma(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_ULP_EQUAL(eve__gamma(EVE_TYPE(0.5)), EVE_TYPE(std::tgamma(EVE_VALUE(0.5))), 1. );
  TTS_ULP_EQUAL(eve__gamma(EVE_TYPE(-35)), EVE_TYPE(std::tgamma(EVE_VALUE(-35))), 0.5);

  TTS_IEEE_EQUAL(eve__gamma(EVE_TYPE( 0 )), eve::inf(eve::as<EVE_TYPE>())  );
  TTS_IEEE_EQUAL(eve__gamma(EVE_TYPE(-0.)), eve::minf(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve__gamma(EVE_TYPE( 1 )), EVE_TYPE(1)           );
  TTS_IEEE_EQUAL(eve__gamma(EVE_TYPE( 2 )), EVE_TYPE(1)           );
  TTS_IEEE_EQUAL(eve__gamma(EVE_TYPE( 3 )), EVE_TYPE(2)           );
  TTS_IEEE_EQUAL(eve__gamma(EVE_TYPE( 5 )), EVE_TYPE(24)          );
}
