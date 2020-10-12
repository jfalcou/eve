//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/y0.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::y0 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::y0(T(0)), T);
}

TTS_CASE_TPL("Check eve::y0 behavior", EVE_TYPE)
{

  auto eve__y0 =  [](auto x) { return eve::y0(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__y0(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__y0(eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__y0(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }
  TTS_ULP_EQUAL(eve__y0(T(10)), T(5.567116728359938e-02), 12.5);
  TTS_ULP_EQUAL(eve__y0(T(5)), T(-3.085176252490338e-01), 1.5);
  TTS_ULP_EQUAL(eve__y0(T(2)), T(  5.103756726497453e-01), 128);
  TTS_ULP_EQUAL(eve__y0(T(1.5)),T(  3.824489237977589e-01 ), 2.0);
  TTS_ULP_EQUAL(eve__y0(T(1)), T( 8.825696421567700e-02), 1);
  TTS_ULP_EQUAL(eve__y0(T(0)), eve::minf(eve::as<T>()), 0.0);
}
