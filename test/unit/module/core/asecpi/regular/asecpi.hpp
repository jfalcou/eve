//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::asecpi return type")
{
  TTS_EXPR_IS(eve::asecpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::asecpi behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::asecpi(eve::Inf<EVE_TYPE>())  , (EVE_TYPE(0.5)) );
    TTS_IEEE_EQUAL(eve::asecpi(eve::Minf<EVE_TYPE>()) , (EVE_TYPE(0.5)) );
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asecpi(eve::Nan<EVE_TYPE>())  , (eve::Nan<EVE_TYPE>()) );
    TTS_ULP_EQUAL(eve::asecpi(eve::Mzero<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 1);
    TTS_ULP_EQUAL(eve::asecpi(EVE_TYPE(0))            , eve::Nan<EVE_TYPE>(), 1);
  }

  TTS_ULP_EQUAL(eve::asecpi(EVE_TYPE(-2.)), (EVE_TYPE(2)/3) , 1   );
  TTS_ULP_EQUAL(eve::asecpi(EVE_TYPE( 2.)), (EVE_TYPE(1)/3) , 1   );
  TTS_ULP_EQUAL(eve::asecpi(EVE_TYPE(-1.)), (EVE_TYPE(1))   , 0.5 );
  TTS_ULP_EQUAL(eve::asecpi(EVE_TYPE( 1.)), (EVE_TYPE(0))   , 0.5 );
}
