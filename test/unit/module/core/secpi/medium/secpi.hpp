//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secpi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
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

TTS_CASE("Check eve::secpi return type")
{
  TTS_EXPR_IS(eve::secpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::secpi behavior")
{
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::secpi)(EVE_TYPE(1)), (EVE_TYPE(-1)), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::secpi)(EVE_TYPE(-1)),(EVE_TYPE(-1)), 0.5);
  TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(EVE_TYPE(0)),(EVE_TYPE(1)));
  TTS_IEEE_EQUAL(eve::medium_(eve::secpi)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(1)));
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(EVE_TYPE(22.5))), (eve::Nan<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(-EVE_TYPE(22.5))),(eve::Nan<EVE_TYPE>()), 0.5);    
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(EVE_TYPE(100000.0))), EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(EVE_TYPE(-100000.0))),EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(EVE_TYPE(1000001.0))), EVE_TYPE(-1), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::secpi)(EVE_TYPE(-100001.0))),EVE_TYPE(-1), 0.5);
}
