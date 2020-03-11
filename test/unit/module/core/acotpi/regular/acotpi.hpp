//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acotpi.hpp>
#include <eve/function/inpi.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::acotpi return type")
{
  TTS_EXPR_IS(eve::acotpi(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::acotpi behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotpi(eve::Nan<EVE_TYPE>()), eve::Nan<EVE_TYPE>(), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotpi(eve::Inf<EVE_TYPE>()),  EVE_TYPE(0), 0);
    TTS_ULP_EQUAL(eve::acotpi(eve::Minf<EVE_TYPE>()), EVE_TYPE(0), 0);
  }

  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE( 0.5)) , eve::inpi(EVE_TYPE(1.107148717794090e+00))  , 1.5 );
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE(-0.5)) , eve::inpi(EVE_TYPE(-1.107148717794090e+00)) , 1.5 );
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE(-1. )) , EVE_TYPE(-0.25)                             , 0.5 );
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE( 1. )) , EVE_TYPE( 0.25)                             , 0.5 );
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE( 0. )) , EVE_TYPE( 0.5 )                             , 0.5 );

  auto inv_smallest = eve::rec(eve::Smallestposval<EVE_TYPE>());
  TTS_ULP_EQUAL(eve::acotpi(eve::Mzero<EVE_TYPE>()) ,  EVE_TYPE(-0.5)                           , 0.5);
  TTS_ULP_EQUAL(eve::acotpi(inv_smallest)       , eve::inpi(eve::Smallestposval<EVE_TYPE>()), 0.5);
}
