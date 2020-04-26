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
#include <eve/function/sec.hpp>
#include <eve/function/secd.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::restricted_(eve::secd) return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::secd)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::restricted_(eve::secd) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::secd)(eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::restricted_(eve::secd)(eve::Inf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::restricted_(eve::secd)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
  }
  TTS_ULP_EQUAL(eve::restricted_(eve::secd)(EVE_TYPE(90)), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::secd)(EVE_TYPE(-90)), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_IEEE_EQUAL((eve::restricted_(eve::secd)(EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_IEEE_EQUAL((eve::restricted_(eve::secd)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(1)));
  TTS_ULP_EQUAL((eve::restricted_(eve::secd)(EVE_TYPE(45))),
                (EVE_TYPE(eve::sec(eve::Pio_4<EVE_VALUE>()))),
                0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::secd)(-EVE_TYPE(45))),
                (EVE_TYPE(eve::sec(-eve::Pio_4<EVE_VALUE>()))),
                0.5);
}
