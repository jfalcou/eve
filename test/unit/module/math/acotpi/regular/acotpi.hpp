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
#include <eve/function/radinpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>


TTS_CASE("Check eve::acotpi return type")
{
  TTS_EXPR_IS(eve::acotpi(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::acotpi behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acotpi(eve::nan(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acotpi(eve::inf(eve::as<EVE_TYPE>())),  EVE_TYPE(0), 0);
    TTS_ULP_EQUAL(eve::acotpi(eve::minf(eve::as<EVE_TYPE>())), EVE_TYPE(0), 0);
  }

  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE( 0.5)) , eve::radinpi(EVE_TYPE(1.107148717794090e+00)) , 1.5 );
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE(-0.5)) , eve::radinpi(EVE_TYPE(-1.107148717794090e+00)), 1.5 );
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE(-1. )) , EVE_TYPE(-0.25)                               , 0.5 );
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE( 1. )) , EVE_TYPE( 0.25)                               , 0.5 );
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE( 0. )) , EVE_TYPE( 0.5 )                               , 0.5 );

  auto inv_smallest = eve::rec(eve::smallestposval(eve::as<EVE_TYPE>()));
  TTS_ULP_EQUAL(eve::acotpi(EVE_TYPE(-0.))       ,  EVE_TYPE(-0.5)                              , 0.5);
  TTS_ULP_EQUAL(eve::acotpi(inv_smallest) , eve::radinpi(eve::smallestposval(eve::as<EVE_TYPE>())), 0.5);
}
