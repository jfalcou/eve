//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/all.hpp>
#include <eve/function/cotd.hpp>
#include <eve/function/cotpi.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::big_(eve::cotd) return type")
{
  TTS_EXPR_IS(eve::big_(eve::cotd)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::big_(eve::cotd) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cotd)(eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::big_(eve::cotd)(eve::Inf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::big_(eve::cotd)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
  }
  auto std_cotd = [](auto e) { return eve::cotpi(double(e) / 180); };

  TTS_ULP_EQUAL(eve::big_(eve::cotd)(EVE_TYPE(1)), EVE_TYPE(std_cotd(1.0)), 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::cotd)(EVE_TYPE(-1)), EVE_TYPE(std_cotd(-1.0)), 3.0);
  TTS_IEEE_EQUAL(eve::big_(eve::cotd)(EVE_TYPE(0)), (eve::Inf<EVE_TYPE>()));
  TTS_IEEE_EQUAL(eve::big_(eve::cotd)(eve::Mzero<EVE_TYPE>()), (eve::Minf<EVE_TYPE>()));
  TTS_ULP_EQUAL((eve::big_(eve::cotd)(EVE_TYPE(45))), EVE_TYPE(std_cotd(45.0)), 3.0);
  TTS_ULP_EQUAL((eve::big_(eve::cotd)(-EVE_TYPE(45))), EVE_TYPE(std_cotd(-45.0)), 3.0);
  TTS_ULP_EQUAL((eve::big_(eve::cotd)(EVE_TYPE(100.0))), EVE_TYPE(std_cotd(100.0)), 3.0);
  TTS_ULP_EQUAL((eve::big_(eve::cotd)(EVE_TYPE(-100.0))), EVE_TYPE(std_cotd(-100.0)), 3.0);
}
