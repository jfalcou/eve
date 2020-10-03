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

TTS_CASE("Check eve::acscd return type")
{
  TTS_EXPR_IS(eve::acscd(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::acscd behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acscd(EVE_TYPE(0))  , eve::nan(eve::as<EVE_TYPE>()), 1);
    TTS_ULP_EQUAL(eve::acscd(EVE_TYPE(-0.)), eve::nan(eve::as<EVE_TYPE>()), 1);
    TTS_IEEE_EQUAL(eve::acscd(eve::nan(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::acscd(eve::inf(eve::as<EVE_TYPE>()))  , (EVE_TYPE(0)) );
    TTS_IEEE_EQUAL(eve::acscd(eve::minf(eve::as<EVE_TYPE>())) , (EVE_TYPE(0)) );
  }

  TTS_ULP_EQUAL(eve::acscd(EVE_TYPE(-2.)),  -EVE_TYPE(30), 1  );
  TTS_ULP_EQUAL(eve::acscd(EVE_TYPE( 2.)),   EVE_TYPE(30), 1  );
  TTS_ULP_EQUAL(eve::acscd(EVE_TYPE(-1.)),  -EVE_TYPE(90), 0.5);
  TTS_ULP_EQUAL(eve::acscd(EVE_TYPE( 1.)),   EVE_TYPE(90), 0.5);
}
