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
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::restricted_(eve::secd) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::restricted_(eve::secd)(T()), T);
}

TTS_CASE_TPL("Check eve::restricted_(eve::secd) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::secd)(eve::Nan<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::restricted_(eve::secd)(eve::Inf<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::restricted_(eve::secd)(eve::Minf<T>()) , eve::Nan<T>() );
  }

  auto ref_secd = [](auto e) { return eve::secpi(double(e) / 180); };

  TTS_IEEE_EQUAL(eve::restricted_(eve::secd)( T( 0) ) , T(1));
  TTS_IEEE_EQUAL(eve::restricted_(eve::secd)( T(-0.)) , T(1));
  TTS_IEEE_EQUAL(eve::restricted_(eve::secd)( T(90) ) , eve::Nan<T>());
  TTS_IEEE_EQUAL(eve::restricted_(eve::secd)(-T(90) ) , eve::Nan<T>());

  TTS_ULP_EQUAL(eve::restricted_(eve::secd)( T( 1)  ) , T(ref_secd(1.0))        , 3);
  TTS_ULP_EQUAL(eve::restricted_(eve::secd)(-T( 1)  ) , T(ref_secd(-1.0))       , 3);
  TTS_ULP_EQUAL(eve::restricted_(eve::secd)( T(45.0)) , T(ref_secd(v_t(45.0)))  , 3);
  TTS_ULP_EQUAL(eve::restricted_(eve::secd)(-T(45.0)) , T(ref_secd(-v_t(45.0))) , 3);
}
