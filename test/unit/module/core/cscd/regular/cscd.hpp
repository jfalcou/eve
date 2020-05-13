//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscd.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::cscd return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::cscd(T()), T);
}

TTS_CASE_TPL("Check eve::cscd behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cscd(eve::Nan<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::cscd(eve::Inf<T>())  , eve::Nan<T>() );
    TTS_IEEE_EQUAL(eve::cscd(eve::Minf<T>()) , eve::Nan<T>() );
  }

  auto ref_cscd = [](auto e) { return eve::cscpi(double(e) / 180); };

  TTS_IEEE_EQUAL(eve::cscd(T( 0 )) , eve::Inf<T>() );
  TTS_IEEE_EQUAL(eve::cscd(T(-0.)) , eve::Minf<T>());

  TTS_ULP_EQUAL(eve::cscd( T(1)  ) , T(ref_cscd(1.0))        , 3);
  TTS_ULP_EQUAL(eve::cscd(-T(1)  ) , T(ref_cscd(-1.0))       , 3);
  TTS_ULP_EQUAL(eve::cscd( T(45) ) , T(ref_cscd(v_t(45.0)))  , 3);
  TTS_ULP_EQUAL(eve::cscd(-T(45) ) , T(ref_cscd(-v_t(45.0))) , 3);
  TTS_ULP_EQUAL(eve::cscd( T(500)) , T(ref_cscd(500.0))      , 3);
  TTS_ULP_EQUAL(eve::cscd(-T(500)) , T(ref_cscd(-500.0))     , 3);
}
