//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cosd.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted(eve::cosd) return type",EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted(eve::cosd)(T(0)), T);
}

TTS_CASE_TPL("Check eve::restricted(eve::cosd) behavior",EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted(eve::cosd)(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cosd)(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::restricted(eve::cosd)(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::restricted(eve::cosd)(T(0    )), T(1)          );
  TTS_IEEE_EQUAL(eve::restricted(eve::cosd)(T(-0.  )), T(1)          );
  TTS_IEEE_EQUAL(eve::restricted(eve::cosd)(T(90.0 )), eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::restricted(eve::cosd)(T(-90.0)), eve::nan(eve::as<T>()) );

  TTS_ULP_EQUAL(eve::medium(eve::cosd)(T(1))      , T(0.9998476951563912391570115588139148516927403105832)    , 0.5 );
  TTS_ULP_EQUAL(eve::medium(eve::cosd)(T(-1))     , T(0.9998476951563912391570115588139148516927403105832)    , 0.5 );
  TTS_ULP_EQUAL(eve::medium(eve::cosd)(T(45.0))   , T(0.70710678118654752440084436210484903928483593768847)   , 0.5 );
  TTS_ULP_EQUAL(eve::medium(eve::cosd)(-T(45.0))  , T(0.70710678118654752440084436210484903928483593768847)   , 0.5 );
}
