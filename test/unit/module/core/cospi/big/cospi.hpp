//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cospi.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <mpreal.h>

TTS_CASE("Check eve::cospi return type")
{
  TTS_EXPR_IS(eve::cospi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::cospi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::big_(eve::cospi)(EVE_TYPE(1)), EVE_TYPE(-1), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cospi)(EVE_TYPE(-1)),EVE_TYPE(-1), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::cospi)(EVE_TYPE(0)), (EVE_TYPE(1)));
  TTS_IEEE_EQUAL(eve::big_(eve::cospi)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(1)));
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(EVE_TYPE(22.5))), (EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(-EVE_TYPE(22.5))),(EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(EVE_TYPE(100000.0))), EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(EVE_TYPE(-100000.0))),EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(EVE_TYPE(100000000.0))), EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(EVE_TYPE(-100000000.0))),EVE_TYPE(1), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cospi)(EVE_TYPE(0.0625))),EVE_TYPE(0.98078528040323044912618223613423903697393373089333), 0.5);
}  
 
 
 
