//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secpi.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::restricted(eve::secpi) return type")
{
  TTS_EXPR_IS(eve::restricted(eve::secpi)(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::restricted(eve::secpi) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::secpi)(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::secpi)(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::secpi)(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::secpi)(EVE_TYPE(0))   , EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::restricted(eve::secpi)(EVE_TYPE(-0.)) , EVE_TYPE(1));

  TTS_ULP_EQUAL(eve::restricted(eve::secpi)(EVE_TYPE(0.125))  , EVE_TYPE(1.08239220029239396879944641073277884012214412675604), 0.5);
  TTS_ULP_EQUAL(eve::restricted(eve::secpi)(-EVE_TYPE(0.125)) , EVE_TYPE(1.08239220029239396879944641073277884012214412675604), 0.5);
}
