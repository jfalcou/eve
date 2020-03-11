//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanpi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::tanpi return type")
{
  TTS_EXPR_IS(eve::tanpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::tanpi behavior")
{
 
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL((eve::tanpi)(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::tanpi)(eve::Inf<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_IEEE_EQUAL((eve::tanpi)(eve::Minf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );   
  }
  TTS_ULP_EQUAL(eve::tanpi(EVE_TYPE(1)), EVE_TYPE(0), 0.5);
  TTS_ULP_EQUAL(eve::tanpi(EVE_TYPE(-1)),EVE_TYPE(0), 0.5);
  TTS_IEEE_EQUAL(eve::tanpi(EVE_TYPE(0)), (EVE_TYPE(0)));
  TTS_EXPECT(eve::all(eve::is_positive(eve::tanpi(eve::Zero<EVE_TYPE>()))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::tanpi(eve::Mzero<EVE_TYPE>()))));    
  TTS_IEEE_EQUAL(eve::tanpi(eve::Mzero<EVE_TYPE>()), (EVE_TYPE(0)));
  TTS_ULP_EQUAL((eve::tanpi(EVE_TYPE(22.5))), (eve::Nan<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL((eve::tanpi(-EVE_TYPE(22.5))),(eve::Nan<EVE_TYPE>()), 0.5);
  TTS_ULP_EQUAL((eve::tanpi(EVE_TYPE(100000.0))), EVE_TYPE(0), 0.5);
  TTS_ULP_EQUAL((eve::tanpi(EVE_TYPE(-100000.0))),EVE_TYPE(0), 0.5);
  TTS_ULP_EQUAL((eve::tanpi(EVE_TYPE(100000000.0))), EVE_TYPE(0), 0.5);
  TTS_ULP_EQUAL((eve::tanpi(EVE_TYPE(-100000000.0))),EVE_TYPE(0), 0.5);
}
