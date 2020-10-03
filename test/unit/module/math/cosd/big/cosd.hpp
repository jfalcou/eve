//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosd.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::big(eve::cosd) return type")
{
  TTS_EXPR_IS(eve::big(eve::cosd)(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::big(eve::cosd) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big(eve::cosd)(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big(eve::cosd)(eve::inf(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::big(eve::cosd)(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::big(eve::cosd)(EVE_TYPE(0   )), EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::big(eve::cosd)(EVE_TYPE(-0. )), EVE_TYPE(1));

  TTS_ULP_EQUAL(eve::big(eve::cosd)(EVE_TYPE(1))      , EVE_TYPE(0.9998476951563912391570115588139148516927403105832)    , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::cosd)(EVE_TYPE(-1))     , EVE_TYPE(0.9998476951563912391570115588139148516927403105832)    , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::cosd)(EVE_TYPE(45.0))   , EVE_TYPE(0.70710678118654752440084436210484903928483593768847)   , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::cosd)(-EVE_TYPE(45.0))  , EVE_TYPE(0.70710678118654752440084436210484903928483593768847)   , 0.5 );
  TTS_ULP_EQUAL(eve::big(eve::cosd)(EVE_TYPE(-500.0)) , EVE_TYPE(-0.7660444431189780352023926505554166739358324570804)   , 3.5 );
  TTS_ULP_EQUAL(eve::big(eve::cosd)(EVE_TYPE(500.0))  , EVE_TYPE(-0.7660444431189780352023926505554166739358324570804)   , 3.5 );
}
