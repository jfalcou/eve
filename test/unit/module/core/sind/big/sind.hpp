//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sind.hpp>
#include <eve/function/sinpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::big_(eve::sind) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::big_(eve::sind)(T()), T);
}

TTS_CASE_TPL("Check eve::big_(eve::sind) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::sind)(eve::Nan<T>() ) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::big_(eve::sind)(eve::Inf<T>() ) , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::big_(eve::sind)(eve::Minf<T>()) , eve::Nan<T>() );
  }

  auto ref_sind = [](auto e) { return eve::sinpi(double(e) / 180); };

  TTS_IEEE_EQUAL(eve::big_(eve::sind)(T( 0 )), T(0) );
  TTS_IEEE_EQUAL(eve::big_(eve::sind)(T(-0.)), T(0) );

  TTS_ULP_EQUAL(eve::big_(eve::sind)( T(1)    ) , T(ref_sind(1.0))        , 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::sind)(-T(1)    ) , T(ref_sind(-1.0))       , 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::sind)( T(45.0) ) , T(ref_sind(v_t(45.0)))  , 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::sind)(-T(45.0) ) , T(ref_sind(-v_t(45.0))) , 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::sind)( T(500.0)) , T(ref_sind(500.0))      , 3.0);
  TTS_ULP_EQUAL(eve::big_(eve::sind)(-T(500.0)) , T(ref_sind(-500.0))     , 3.0);
}
