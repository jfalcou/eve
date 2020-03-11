//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acot.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::acot return type")
{
  TTS_EXPR_IS(eve::acot(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::acot behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acot(eve::Nan<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acot(eve::Inf<EVE_TYPE>()) , EVE_TYPE(0), 0);
    TTS_ULP_EQUAL(eve::acot(eve::Minf<EVE_TYPE>()), EVE_TYPE(0), 0);
  }

  TTS_ULP_EQUAL(eve::acot(EVE_TYPE( 0.5))         ,  EVE_TYPE(1.107148717794090e+00)  , 1   );
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE(-0.5))         ,  EVE_TYPE(-1.107148717794090e+00) , 1   );
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE(-1. ))         , -eve::Pio_4<EVE_TYPE>()           , 0.5 );
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE( 1. ))         ,  eve::Pio_4<EVE_TYPE>()           , 0.5 );
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE( 0. ))         ,  eve::Pio_2<EVE_TYPE>()           , 1   );

  auto inv_smallest = eve::rec(eve::Smallestposval<EVE_TYPE>());
  TTS_ULP_EQUAL(eve::acot(eve::Mzero<EVE_TYPE>()) , -eve::Pio_2<EVE_TYPE>()           , 1   );
  TTS_ULP_EQUAL(eve::acot(inv_smallest)       ,  eve::Smallestposval<EVE_TYPE>()  , 0.5 );
}
