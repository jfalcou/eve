//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/erfinv.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::erfinv return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::erfinv(T(0)), T);
}

TTS_CASE_TPL("Check eve::erfinv behavior", EVE_TYPE)
{
  auto eve__erfinv =  [](auto x) { return eve::erfinv(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__erfinv(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__erfinv(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__erfinv(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve__erfinv(T(35)), eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve__erfinv(T(-35)), eve::nan(eve::as<T>()), 0.5);

  TTS_IEEE_EQUAL(eve__erfinv(T( 0 )),T(0)  );
  TTS_IEEE_EQUAL(eve__erfinv(T(-0.)), T(0) );
  TTS_ULP_EQUAL(eve__erfinv(T( 0.1 )), T( boost::math::erf_inv(0.1)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T( 0.2 )), T( boost::math::erf_inv(0.2)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T( 0.3 )), T( boost::math::erf_inv(0.3)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T( 0.5 )), T( boost::math::erf_inv(0.5)),  1 );
  TTS_ULP_EQUAL(eve__erfinv(T( 0.15)), T( boost::math::erf_inv(0.15)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T( 0.75)), T( boost::math::erf_inv(0.75)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T(- 0.1 )), T( boost::math::erf_inv(-0.1)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T( -0.2 )), T( boost::math::erf_inv(-0.2)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T( -0.3 )), T( boost::math::erf_inv(-0.3)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T( -0.5 )), T( boost::math::erf_inv(-0.5)),  1 );
  TTS_ULP_EQUAL(eve__erfinv(T( -0.15)), T( boost::math::erf_inv(-0.15)), 0.5 );
  TTS_ULP_EQUAL(eve__erfinv(T( -0.75)), T( boost::math::erf_inv(-0.75)), 0.5 );
}
