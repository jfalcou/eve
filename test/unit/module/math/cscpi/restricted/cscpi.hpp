//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>

TTS_CASE_TPL("Check eve::restricted(eve::cscpi) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::cscpi)(T()), T);
}

TTS_CASE_TPL("Check eve::restricted(eve::cscpi) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::cscpi)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cscpi)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cscpi)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::cscpi)(T(0))     , eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::restricted(eve::cscpi)(T(-0.))   , eve::minf(eve::as<T>()));
  TTS_ULP_EQUAL(eve::restricted(eve::cscpi)(T(0.125))  , T(2.6131259297527530557132863468543743071675223766986)  , 0.5);
  TTS_ULP_EQUAL(eve::restricted(eve::cscpi)(-T(0.125)) , T(-2.6131259297527530557132863468543743071675223766986) , 0.5);
}

