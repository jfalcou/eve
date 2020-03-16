//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpi.hpp>
#include <eve/function/sin.hpp>    
#include <eve/constant/mzero.hpp> 
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/next.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>  
#include <eve/function/all.hpp>    
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sinpi return type")
{
  TTS_EXPR_IS(eve::sinpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::sinpi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::sinpi)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sinpi)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::sinpi)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)(EVE_TYPE(1)), (EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::sinpi)(EVE_TYPE(-1)),(EVE_TYPE(0)), 0.5);
  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::sinpi)(eve::Zero<EVE_TYPE>()))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::sinpi)(eve::Mzero<EVE_TYPE>()))));    
  TTS_IEEE_EQUAL(eve::medium_(eve::sinpi)(EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_IEEE_EQUAL(eve::medium_(eve::sinpi)(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(0)));
  TTS_ULP_EQUAL((eve::medium_(eve::sinpi)(EVE_TYPE(22.5))), (EVE_TYPE(1)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sinpi)(-EVE_TYPE(22.5))),(EVE_TYPE(-1)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sinpi)(EVE_TYPE(100000.0))), (EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sinpi)(EVE_TYPE(-100000.0))),(EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sinpi)(EVE_TYPE(100000000.0))), (EVE_TYPE(0)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::sinpi)(EVE_TYPE(-100000000.0))),(EVE_TYPE(0)), 0.5);
}

 
 
