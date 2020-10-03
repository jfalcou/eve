//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secpi.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::big(eve::secpi) return type")
{
  TTS_EXPR_IS(eve::big(eve::secpi)(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::big(eve::secpi) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::secpi)(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big(eve::secpi)(eve::inf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big(eve::secpi)(eve::minf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::big(eve::secpi)(EVE_TYPE( 0 )), EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::big(eve::secpi)(EVE_TYPE(-0.)), EVE_TYPE(1));

  TTS_ULP_EQUAL(eve::big(eve::secpi)( EVE_TYPE( 1))       ,-EVE_TYPE(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::secpi)(-EVE_TYPE( 1))       ,-EVE_TYPE(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::secpi)( EVE_TYPE(22.5))     , eve::nan(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::secpi)(-EVE_TYPE(22.5))     , eve::nan(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::secpi)( EVE_TYPE(100000.0)) , EVE_TYPE(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::secpi)(-EVE_TYPE(100000.0)) , EVE_TYPE(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::secpi)( EVE_TYPE(1000001.0)),-EVE_TYPE(1)          , 0.5);
  TTS_ULP_EQUAL(eve::big(eve::secpi)(-EVE_TYPE(100001.0)) ,-EVE_TYPE(1)          , 0.5);
  auto z = eve::maxflint(eve::as<EVE_TYPE>())*10;
  TTS_ULP_EQUAL(eve::big(eve::secpi)(z) , EVE_TYPE(1) , 0.5);}
