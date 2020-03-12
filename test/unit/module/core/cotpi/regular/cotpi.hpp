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
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_even.hpp>
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
    TTS_IEEE_EQUAL((eve::cotpi)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::cotpi)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::cotpi)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL((eve::cotpi)(EVE_TYPE(1)), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL((eve::cotpi)(EVE_TYPE(-1)),eve::Nan<EVE_TYPE>(), 0.5);
  TTS_IEEE_EQUAL((eve::cotpi)(EVE_TYPE(0)), (eve::Inf<EVE_TYPE>()));
  TTS_IEEE_EQUAL((eve::cotpi)(eve::Mzero<EVE_TYPE>()), (eve::Minf<EVE_TYPE>()));
  TTS_ULP_EQUAL(((eve::cotpi)(EVE_TYPE(22.5))), (EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL(((eve::cotpi)(-EVE_TYPE(22.5))),(EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL(((eve::cotpi)(EVE_TYPE(100000.0))), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(((eve::cotpi)(EVE_TYPE(-100000.0))),eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(((eve::cotpi)(EVE_TYPE(100000000.0))), eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(((eve::cotpi)(EVE_TYPE(eve::Valmax<EVE_TYPE>()))),eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(((eve::cotpi)(EVE_TYPE(eve::Valmax<EVE_TYPE>()))/10),eve::Nan<EVE_TYPE>(), 0.5); 
}
