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
    TTS_IEEE_EQUAL(eve::medium_(eve::cosd)(eve::Nan<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::medium_(eve::cosd)(eve::Inf<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::medium_(eve::cosd)(eve::Minf<T>()) , eve::Nan<T>() );
  }

  using v_t = eve::element_type_t<T>;
  auto ref_cosd = [](auto e) { return eve::cospi(double(e) / 180.); };

  TTS_IEEE_EQUAL(eve::medium_(eve::cosd)(T(0   )), T(1));
  TTS_IEEE_EQUAL(eve::medium_(eve::cosd)(T(-0. )), T(1));

  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(T(1))      , T(ref_cosd(1.0))        , 0.5 );
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(T(-1))     , T(ref_cosd(-1.0))       , 0.5 );
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(T(45.0))   , T(ref_cosd(v_t(45.0)))  , 0.5 );
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(-T(45.0))  , T(ref_cosd(-v_t(45.0))) , 0.5 );
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(T(500.0))  , T(ref_cosd(500.0))      , 2   );
  TTS_ULP_EQUAL(eve::medium_(eve::cosd)(T(-500.0)) , T(ref_cosd(-500.0))     , 2   );
}
