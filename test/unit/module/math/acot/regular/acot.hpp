//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <cmath>

TTS_CASE("Check eve::acot return type")
{
  TTS_EXPR_IS(eve::acot(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::acot behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acot(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acot(eve::inf(eve::as<EVE_TYPE>())) , EVE_TYPE(0), 0);
    TTS_ULP_EQUAL(eve::acot(eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE(0), 0);
  }

  TTS_ULP_EQUAL(eve::acot(EVE_TYPE( 0.5))         ,  EVE_TYPE(1.107148717794090e+00)  , 1   );
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE(-0.5))         ,  EVE_TYPE(-1.107148717794090e+00) , 1   );
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE(-1. ))         , -eve::pio_4(eve::as<EVE_TYPE>())           , 0.5 );
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE( 1. ))         ,  eve::pio_4(eve::as<EVE_TYPE>())           , 0.5 );
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE( 0. ))         ,  eve::pio_2(eve::as<EVE_TYPE>())           , 1   );

  auto inv_smallest = eve::rec(eve::smallestposval(eve::as<EVE_TYPE>()));
  TTS_ULP_EQUAL(eve::acot(EVE_TYPE(-0.)) , -eve::pio_2(eve::as<EVE_TYPE>())           , 1   );
  TTS_ULP_EQUAL(eve::acot(inv_smallest)       ,  eve::smallestposval(eve::as<EVE_TYPE>())  , 0.5 );
}
