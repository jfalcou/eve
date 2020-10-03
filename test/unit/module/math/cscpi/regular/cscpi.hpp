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

TTS_CASE("Check eve::cscpi return type")
{
  TTS_EXPR_IS(eve::cscpi(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::cscpi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cscpi(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cscpi(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cscpi(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::cscpi(EVE_TYPE(0))  , eve::inf(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::cscpi(EVE_TYPE(-0.)), eve::minf(eve::as<EVE_TYPE>()));

  TTS_ULP_EQUAL(eve::cscpi(-EVE_TYPE(100000000.0) ) , eve::nan(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::cscpi(-EVE_TYPE(100000.0)    ) , eve::nan(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::cscpi(-EVE_TYPE(100000.5)    ) , EVE_TYPE(-1)           , 0.5);
  TTS_ULP_EQUAL(eve::cscpi( EVE_TYPE(1)           ) , eve::nan(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::cscpi(-EVE_TYPE(1)           ) , eve::nan(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::cscpi(EVE_TYPE(0.125)        ) , EVE_TYPE(2.6131259297527530557132863468543743071675223766986)  , 0.5);
  TTS_ULP_EQUAL(eve::cscpi(-EVE_TYPE(0.125)       ) , EVE_TYPE(-2.6131259297527530557132863468543743071675223766986) , 0.5);
  TTS_ULP_EQUAL(eve::cscpi(-EVE_TYPE(22.5)        ) , EVE_TYPE(-1)           , 0.5);
  TTS_ULP_EQUAL(eve::cscpi(-EVE_TYPE(22.25)       ) ,-eve::sqrt_2(eve::as<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL(eve::cscpi( EVE_TYPE(22.25)       ) , eve::sqrt_2(eve::as<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL(eve::cscpi( EVE_TYPE(22.5)        ) , EVE_TYPE(1)            , 0.5);
  TTS_ULP_EQUAL(eve::cscpi( EVE_TYPE(100000.0)    ) , eve::nan(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::cscpi( EVE_TYPE(100000.5)    ) , EVE_TYPE(1)            , 0.5);
  TTS_ULP_EQUAL(eve::cscpi( EVE_TYPE(100000000.0) ) , eve::nan(eve::as<EVE_TYPE>())   , 0.5);
}
