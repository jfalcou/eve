//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secd.hpp>
#include <eve/function/secpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::big_(eve::secd) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big_(eve::secd)(T()), T);
}

TTS_CASE_TPL("Check eve::big_(eve::secd) behavior", EVE_TYPE)
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::secd)(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::secd)(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::secd)(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::big_(eve::secd)(T( 0  )), T(1));
  TTS_IEEE_EQUAL(eve::big_(eve::secd)(T(-0. )), T(1));

  TTS_ULP_EQUAL(eve::big_(eve::secd)( T(  1)  ) , T(1.00015232804390766542842643421257380147891180422143)  , 3);
  TTS_ULP_EQUAL(eve::big_(eve::secd)(-T(  1)  ) , T(1.00015232804390766542842643421257380147891180422143)  , 3);
  TTS_ULP_EQUAL(eve::big_(eve::secd)( T( 45.0)) , T(1.41421356237309504880168872420969807856967187537694)  , 5);
  TTS_ULP_EQUAL(eve::big_(eve::secd)(-T( 45.0)) , T(1.41421356237309504880168872420969807856967187537694)  , 5);
  TTS_ULP_EQUAL(eve::big_(eve::secd)( T(500.0)) , T(-1.30540728933227860459313349292274081599849729126374) , 3);
  TTS_ULP_EQUAL(eve::big_(eve::secd)(-T(500.0)) , T(-1.30540728933227860459313349292274081599849729126374) , 3);
  auto z = eve::Maxflint<T>()*180;
  TTS_ULP_EQUAL(eve::big_(eve::secd)(z) , T(1) , 0.5);
}
