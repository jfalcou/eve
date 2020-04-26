//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sind.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::medium_(eve::sind) return type")
{
  TTS_EXPR_IS(eve::medium_(eve::sind)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::medium_(eve::sind) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::sind)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sind)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sind)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );
  }
  auto std_sind = [](auto e) { return eve::sinpi(double(e)/180); };

  TTS_ULP_EQUAL(eve::medium_(eve::sind)(EVE_TYPE(1)), EVE_TYPE(std_sind(1.0)), 3.0);
  TTS_ULP_EQUAL(eve::medium_(eve::sind)(EVE_TYPE(-1)),EVE_TYPE(std_sind(-1.0)), 3.0);
  TTS_IEEE_EQUAL(eve::medium_(eve::sind)(EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_IEEE_EQUAL(eve::medium_(eve::sind)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(0)));
  TTS_ULP_EQUAL((eve::medium_(eve::sind)(EVE_TYPE(45.0))), (EVE_TYPE(std_sind(EVE_VALUE(45.0)))), 3.0);
  TTS_ULP_EQUAL((eve::medium_(eve::sind)(-EVE_TYPE(45.0))),(EVE_TYPE(std_sind(-EVE_VALUE(45.0)))), 3.0);
  TTS_ULP_EQUAL((eve::medium_(eve::sind)(EVE_TYPE(500.0))), EVE_TYPE(std_sind(500.0)), 3.0);
  TTS_ULP_EQUAL((eve::medium_(eve::sind)(EVE_TYPE(-500.0))),EVE_TYPE(std_sind(-500.0)), 3.0);

}
