//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotd.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cotd return type")
{
  TTS_EXPR_IS(eve::cotd(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::cotd behavior")
{
  auto std_cotd = [](auto e) { return eve::cotpi(double(e)/180); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cotd(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cotd(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::cotd(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );
  }
  TTS_ULP_EQUAL(eve::cotd(EVE_TYPE(1)), EVE_TYPE(std_cotd(1.0)), 3.0);
  TTS_ULP_EQUAL(eve::cotd(EVE_TYPE(-1)),EVE_TYPE(std_cotd(-1.0)), 3.0);
  TTS_IEEE_EQUAL((eve::cotd(EVE_TYPE(0))),  (eve::Inf<EVE_TYPE>()));
  TTS_IEEE_EQUAL((eve::cotd(eve::Mzero<EVE_TYPE>())),  (eve::Minf<EVE_TYPE>()));
  TTS_ULP_EQUAL((eve::restricted_(eve::cotd)(EVE_TYPE(45))),  EVE_TYPE(std_cotd(45.0)), 3.0);
  TTS_ULP_EQUAL((eve::restricted_(eve::cotd)(-EVE_TYPE(45))), EVE_TYPE(std_cotd(-45.0)), 3.0);
  TTS_ULP_EQUAL(eve::cotd(EVE_TYPE(100.0)), EVE_TYPE(std_cotd(100.0)), 3.0);
  TTS_ULP_EQUAL(eve::cotd(EVE_TYPE(-100.0)),EVE_TYPE(std_cotd(-100.0)), 3.0);
}
