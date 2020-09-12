//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/csc.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::medium_(eve::csc) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::medium_(eve::csc)(T()), T);
}

TTS_CASE_TPL("Check eve::medium_(eve::csc) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto ref_csc =  [](auto x){return eve::rec(std::sin(double(x)));};

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::csc)(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::csc)(eve::inf(eve::as<T>())) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::csc)(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  TTS_IEEE_EQUAL(eve::medium_(eve::csc)(T( 0 )), T(ref_csc(v_t(0.0))));
  TTS_IEEE_EQUAL(eve::medium_(eve::csc)(T(-0.)), T(ref_csc(v_t(-0.0))));

  TTS_ULP_EQUAL(eve::medium_(eve::csc)( T(1)            ) , T(ref_csc(1.0))               , 1.0 );
  TTS_ULP_EQUAL(eve::medium_(eve::csc)(-T(1)            ) , T(ref_csc(-1.0))              , 1.0 );
  TTS_ULP_EQUAL(eve::medium_(eve::csc)(-eve::pio_4(eve::as<T>()) ) , T(ref_csc(-eve::pio_4(eve::as<v_t>()))), 0.75);
  TTS_ULP_EQUAL(eve::medium_(eve::csc)( eve::pio_4(eve::as<T>()) ) , T(ref_csc(eve::pio_4(eve::as<v_t>()))) , 0.75);
  TTS_ULP_EQUAL(eve::medium_(eve::csc)( T(100.0)        ) , T(ref_csc(v_t(100.0)))        , 1.5 );
  TTS_ULP_EQUAL(eve::medium_(eve::csc)(-T(100.0)        ) , T(ref_csc(v_t(-100.0)))       , 1.5 );
  TTS_ULP_EQUAL(eve::medium_(eve::csc)( T(100000.0)     ) , T(ref_csc(v_t(100000.0)))     , 0.5 );
  TTS_ULP_EQUAL(eve::medium_(eve::csc)(-T(100000.0)     ) , T(ref_csc(v_t(-100000.0)))    , 0.5 );
}
