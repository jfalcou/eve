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
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::medium_(eve::cosd) return type",EVE_TYPE)
{
  TTS_EXPR_IS(eve::medium_(eve::cosd)(T(0)), T);
}

TTS_CASE_TPL("Check eve::medium_(eve::cosd) behavior",EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::cosd)(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cosd)(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cosd)(eve::Minf<T>()) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::big_(eve::cosd)(T(0   )), T(1));
  TTS_IEEE_EQUAL(eve::big_(eve::cosd)(T(-0. )), T(1));

  TTS_ULP_EQUAL(eve::big_(eve::cosd)(T(1))      , T(0.9998476951563912391570115588139148516927403105832)    , 0.5 );
  TTS_ULP_EQUAL(eve::big_(eve::cosd)(T(-1))     , T(0.9998476951563912391570115588139148516927403105832)    , 0.5 );
  TTS_ULP_EQUAL(eve::big_(eve::cosd)(T(45.0))   , T(0.70710678118654752440084436210484903928483593768847)   , 0.5 );
  TTS_ULP_EQUAL(eve::big_(eve::cosd)(-T(45.0))  , T(0.70710678118654752440084436210484903928483593768847)   , 0.5 );
  TTS_ULP_EQUAL(eve::big_(eve::cosd)(T(-500.0)) , T(-0.7660444431189780352023926505554166739358324570804)   , 3.5 );
  TTS_ULP_EQUAL(eve::big_(eve::cosd)(T(500.0))  , T(-0.7660444431189780352023926505554166739358324570804)   , 3.5 );
}
