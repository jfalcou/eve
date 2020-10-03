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


TTS_CASE("Check eve::acotd return type")
{
  TTS_EXPR_IS(eve::acotd(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::acotd behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::inf(eve::as<EVE_TYPE>()))  , EVE_TYPE(0), 0);
    TTS_ULP_EQUAL(eve::acotd(eve::minf(eve::as<EVE_TYPE>())) , EVE_TYPE(0), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotd(eve::nan(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE( 0.5)), EVE_TYPE( 63.4349488229220) , 1   );
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE(-0.5)), EVE_TYPE(-63.4349488229220) , 1   );
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE(-1. )), EVE_TYPE(-45)               , 0.5 );
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE( 1. )), EVE_TYPE( 45)               , 0.5 );
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE( 0. )), EVE_TYPE( 90)               , 0.5 );

  auto inv_smallest = eve::rec(eve::smallestposval(eve::as<EVE_TYPE>()));
  TTS_ULP_EQUAL(eve::acotd(EVE_TYPE(-0.))      ,  EVE_TYPE(-90)                             , 0.5);
  TTS_ULP_EQUAL(eve::acotd(inv_smallest), eve::radindeg(eve::smallestposval(eve::as<EVE_TYPE>())), 0.5);
}
