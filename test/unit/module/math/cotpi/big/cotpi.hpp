//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::cotpi return type")
{
  TTS_EXPR_IS(eve::cotpi(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::eve::cotpi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::cotpi)(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big(eve::cotpi)(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big(eve::cotpi)(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::big(eve::cotpi)(EVE_TYPE( 0 )), eve::rec(EVE_TYPE( 0  )));
  TTS_IEEE_EQUAL(eve::big(eve::cotpi)(EVE_TYPE(-0.)), eve::rec(EVE_TYPE(-0.0)));

  TTS_ULP_EQUAL(eve::big(eve::cotpi)( EVE_TYPE( 1)      ) , eve::nan(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)( EVE_TYPE(-1)      ) , eve::nan(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)( EVE_TYPE(22)      ) , eve::nan(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)(-EVE_TYPE(22)      ) , eve::nan(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)( EVE_TYPE(100000.5)) , EVE_TYPE(0)          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::cotpi)(-EVE_TYPE(100000.5)) , EVE_TYPE(0)          , 0.5);
}

