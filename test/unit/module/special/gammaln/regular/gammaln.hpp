//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gammaln.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::gammaln return type")
{
  TTS_EXPR_IS(eve::gammaln(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::gammaln behavior")
{
  auto eve__gammaln =  [](auto x) { return eve::gammaln(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__gammaln(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve__gammaln(eve::inf(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve__gammaln(eve::minf(eve::as<EVE_TYPE>())) , eve::inf(eve::as<EVE_TYPE>()) );
  }

  TTS_ULP_EQUAL(eve__gammaln(EVE_TYPE(0.5)), EVE_TYPE(std::lgamma(EVE_VALUE(0.5))), 1. );
  TTS_ULP_EQUAL(eve__gammaln(EVE_TYPE(-35)), EVE_TYPE(std::lgamma(EVE_VALUE(-35))), 0.5);

  TTS_IEEE_EQUAL(eve__gammaln(EVE_TYPE( 0 )), eve::inf(eve::as<EVE_TYPE>())  );
  TTS_IEEE_EQUAL(eve__gammaln(EVE_TYPE(-0.)), eve::inf(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve__gammaln(EVE_TYPE( 1 )), EVE_TYPE(0)           );
  TTS_IEEE_EQUAL(eve__gammaln(EVE_TYPE( 2 )), EVE_TYPE(0)           );
  TTS_IEEE_EQUAL(eve__gammaln(EVE_TYPE( 3 )), EVE_TYPE(std::log(2.0))  );
  TTS_IEEE_EQUAL(eve__gammaln(EVE_TYPE( 5 )), EVE_TYPE(std::log(24.0)) );
}
