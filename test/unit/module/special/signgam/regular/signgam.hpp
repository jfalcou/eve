//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/signgam.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::signgam return type")
{
  TTS_EXPR_IS(eve::signgam(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::signgam behavior")
{
  auto eve__signgam =  [](auto x) { return eve::signgam(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__signgam(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve__signgam(eve::inf(eve::as<EVE_TYPE>()))  , eve::one(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve__signgam(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_EQUAL(eve__signgam(EVE_TYPE(0.5)), EVE_TYPE(1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE(-35)), eve::nan(eve::as<EVE_TYPE>()));

  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( 0 )), EVE_TYPE(1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE(-0.)), EVE_TYPE(-1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( 1 )), EVE_TYPE(1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( 2 )), EVE_TYPE(1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( 3 )), EVE_TYPE(1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( 5 )), EVE_TYPE(1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( -1.1 )), EVE_TYPE(1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( -2.1 )), EVE_TYPE(-1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( -3.1 )), EVE_TYPE(1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( -4.1 )), EVE_TYPE(-1) );
  TTS_IEEE_EQUAL(eve__signgam(EVE_TYPE( -5.1 )), EVE_TYPE(1) );
}
