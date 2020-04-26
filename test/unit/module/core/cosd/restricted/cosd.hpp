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
#include <eve/function/cos.hpp>
#include <eve/function/cosd.hpp>
#include <eve/platform.hpp>

#include <cmath>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::restricted_(eve::cosd) return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::cosd)(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::restricted_(eve::cosd) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cosd)(eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::restricted_(eve::cosd)(eve::Inf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::restricted_(eve::cosd)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
  }
  TTS_ULP_EQUAL(eve::restricted_(eve::cosd)(EVE_TYPE(90)), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::cosd)(EVE_TYPE(-90)), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_IEEE_EQUAL((eve::restricted_(eve::cosd)(EVE_TYPE(0))), (EVE_TYPE(1)));
  TTS_IEEE_EQUAL((eve::restricted_(eve::cosd)(eve::Mzero<EVE_TYPE>())), (EVE_TYPE(1)));
  TTS_ULP_EQUAL((eve::restricted_(eve::cosd)(EVE_TYPE(45))),
                (EVE_TYPE(std::cos(eve::Pio_4<EVE_VALUE>()))),
                0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::cosd)(-EVE_TYPE(45))),
                (EVE_TYPE(std::cos(-eve::Pio_4<EVE_VALUE>()))),
                0.5);
}
