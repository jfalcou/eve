//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asec.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::asec return type")
{
  TTS_EXPR_IS(eve::asec(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::asec behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::asec(eve::Inf<EVE_TYPE>()),  (eve::Pio_2<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::asec(eve::Minf<EVE_TYPE>()), (eve::Pio_2<EVE_TYPE>()) );
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asec((EVE_TYPE(0)))          , eve::Nan<EVE_TYPE>(), 1);
    TTS_ULP_EQUAL(eve::asec(eve::Mzero<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 1);
    TTS_IEEE_EQUAL(eve::asec(eve::Nan<EVE_TYPE>())  , (eve::Nan<EVE_TYPE>()) );
  }

  TTS_ULP_EQUAL(eve::asec(EVE_TYPE(-2)) , 2*eve::Pi<EVE_TYPE>()/3 , 1   );
  TTS_ULP_EQUAL(eve::asec(EVE_TYPE( 2)) , eve::Pi<EVE_TYPE>()/3   , 1   );
  TTS_ULP_EQUAL(eve::asec(EVE_TYPE(-1)) , eve::Pi<EVE_TYPE>()     , 0.5 );
  TTS_ULP_EQUAL(eve::asec(EVE_TYPE( 1)) , (EVE_TYPE(0))           , 0.5 );
}
