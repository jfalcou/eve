//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecd.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::asecd return type")
{
  TTS_EXPR_IS(eve::asecd(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::asecd behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asecd(eve::Inf<EVE_TYPE>()) , (EVE_TYPE(90)), 0.5);
    TTS_ULP_EQUAL(eve::asecd(eve::Minf<EVE_TYPE>()), (EVE_TYPE(90)), 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asecd(eve::Nan<EVE_TYPE>()) , (eve::Nan<EVE_TYPE>()) );
    TTS_ULP_EQUAL(eve::asecd(EVE_TYPE(0))           , eve::Nan<EVE_TYPE>(), 1);
    TTS_ULP_EQUAL(eve::asecd(eve::Mzero<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 1);
  }

  TTS_ULP_EQUAL(eve::asecd(EVE_TYPE(-2.)), (EVE_TYPE(360)/3) , 1   );
  TTS_ULP_EQUAL(eve::asecd(EVE_TYPE( 2.)), (EVE_TYPE(180)/3) , 1   );
  TTS_ULP_EQUAL(eve::asecd(EVE_TYPE(-1.)), (EVE_TYPE(180))   , 0.5 );
  TTS_ULP_EQUAL(eve::asecd(EVE_TYPE( 1.)), (EVE_TYPE(0))     , 0.5 );
}
