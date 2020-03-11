//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acotd.hpp>
#include <eve/function/indeg.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::acotd return type")
{
  TTS_EXPR_IS(eve::acotd(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::acotd behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::Inf<EVE_TYPE>())  , EVE_TYPE(0), 0);
    TTS_ULP_EQUAL(eve::acotd(eve::Minf<EVE_TYPE>()) , EVE_TYPE(0), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
  }

  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE( 0.5)), EVE_TYPE( 63.4349488229220) , 1   );
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE(-0.5)), EVE_TYPE(-63.4349488229220) , 1   );
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE(-1. )), EVE_TYPE(-45)               , 0.5 );
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE( 1. )), EVE_TYPE( 45)               , 0.5 );
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE( 0. )), EVE_TYPE( 90)               , 0.5 );

  auto inv_smallest = eve::rec(eve::Smallestposval<EVE_TYPE>());
  TTS_ULP_EQUAL(eve::acotd(eve::Mzero<EVE_TYPE>()),  EVE_TYPE(-90)                              , 0.5);
  TTS_ULP_EQUAL(eve::acotd(inv_smallest)      , eve::indeg(eve::Smallestposval<EVE_TYPE>()) , 0.5);
}
