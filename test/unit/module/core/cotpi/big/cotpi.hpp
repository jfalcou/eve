//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cotpi return type")
{
  TTS_EXPR_IS(eve::cotpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::cotpi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cotpi)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cotpi)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cotpi)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::big_(eve::cotpi)(EVE_TYPE(1)), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cotpi)(EVE_TYPE(-1)),eve::Nan<EVE_TYPE>(), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::cotpi)(EVE_TYPE(0)),  eve::rec((EVE_TYPE(0))));
  TTS_IEEE_EQUAL(eve::big_(eve::cotpi)(eve::Mzero<EVE_TYPE>()),  eve::rec((EVE_TYPE(-0.0))));
  TTS_ULP_EQUAL((eve::big_(eve::cotpi)(EVE_TYPE(22))), (eve::Nan<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cotpi)(-EVE_TYPE(22))),(eve::Nan<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cotpi)(EVE_TYPE(100000.5))), EVE_TYPE(0), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cotpi)(EVE_TYPE(-100000.5))),EVE_TYPE(0), 0.5);
}

