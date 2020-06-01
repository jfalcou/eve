//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acotd.hpp>
#include <eve/function/radindeg.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::acotd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::acotd(T(0)), T);
}

TTS_CASE_TPL("Check eve::acotd behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::Inf<T>())  , T(0), 0);
    TTS_ULP_EQUAL(eve::acotd(eve::Minf<T>()) , T(0), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::Nan<T>()), eve::Nan<T>(), 0);
  }

  TTS_ULP_EQUAL(eve::acotd(T( 0.5)), T( 63.4349488229220) , 1   );
  TTS_ULP_EQUAL(eve::acotd(T(-0.5)), T(-63.4349488229220) , 1   );
  TTS_ULP_EQUAL(eve::acotd(T(-1. )), T(-45)               , 0.5 );
  TTS_ULP_EQUAL(eve::acotd(T( 1. )), T( 45)               , 0.5 );
  TTS_ULP_EQUAL(eve::acotd(T( 0. )), T( 90)               , 0.5 );

  auto inv_smallest = eve::rec(eve::Smallestposval<T>());
  TTS_ULP_EQUAL(eve::acotd(T(-0.))      ,  T(-90)                             , 0.5);
  TTS_ULP_EQUAL(eve::acotd(inv_smallest), eve::radindeg(eve::Smallestposval<T>()), 0.5);
}
