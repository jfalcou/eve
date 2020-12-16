//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/erfc.hpp>
#include <eve/constant/halfeps.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::erfc return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::erfc(T()), T);
}

TTS_CASE_TPL("Check eve::eve::erfc behavior", EVE_TYPE)
{
//  using v_t = eve::element_type_t<T>;
  auto eve__erfc =  [](auto x) { return eve::erfc(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve__erfc(eve::inf(eve::as<T>())), T(0), 0);
    TTS_ULP_EQUAL(eve__erfc(eve::minf(eve::as<T>())), T(2), 0);
    TTS_ULP_EQUAL(eve__erfc(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
  }

  // the numérical value were given by sollya.
  TTS_ULP_EQUAL(eve__erfc(T(0)), T(1), 1);
  TTS_ULP_EQUAL(eve__erfc(T(0.25)), T(0.7236736098317630670149317322351842879346460221077), 0.5);
  TTS_ULP_EQUAL(eve__erfc(T(0.5)), T(0.47950012218695346231725334610803547126354842424203), 1.5);
  TTS_ULP_EQUAL(eve__erfc(T(1)), T(0.157299207050285130658779364917), 0.5);
  TTS_ULP_EQUAL(eve__erfc(T(2)), T(0.00467773498104726583793074363275), 1);
  TTS_ULP_EQUAL(eve__erfc(T(6)), T(2.15197367124989131165933503991873846304775140616887e-17),  0.5);
  TTS_ULP_EQUAL(eve__erfc(T(10)),T( 2.0884875837625447570007862949577886115608181193212e-45),  0.5);
  TTS_ULP_EQUAL(eve__erfc(T(15)),T(7.2129941724512066665650665586929271099340909298254e-100),  0.5);
  TTS_ULP_EQUAL(eve__erfc(-T(0.5)),  T(1.52049987781304653768274665389196452873645157575797),        0.5);
  TTS_ULP_EQUAL(eve__erfc(T(-1)),    T(1.8427007929497148693412206350826092592960669979663), 0.5);
  TTS_ULP_EQUAL(eve__erfc(T(-2)),    T(1.99532226501895273416206925636725292861089179704005), 0.5);
  TTS_ULP_EQUAL(eve__erfc(T(-6)),    T(1.9999999999999999784802632875010868834066496008126), 0);
  TTS_ULP_EQUAL(eve__erfc(T(-10)),   T(2), 0);
  TTS_ULP_EQUAL(eve__erfc(T(27)), T(0), 0);
  TTS_ULP_EQUAL(eve__erfc(T(-27)), T(2), 0);
  TTS_ULP_EQUAL(eve__erfc(-T(0.25)), T(1.27632639016823693298506826776481571206535397789232),        0.5);
}
