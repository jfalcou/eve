//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/erf_inv.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::erf_inv return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::erf_inv(T(0)), T);
}

TTS_CASE_TPL("Check eve::erf_inv behavior", EVE_TYPE)
{
  auto eve__erf_inv =  [](auto x) { return eve::erf_inv(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__erf_inv(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__erf_inv(eve::inf(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__erf_inv(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve__erf_inv(T(35)), eve::nan(eve::as<T>()), 0.5);
  TTS_ULP_EQUAL(eve__erf_inv(T(-35)), eve::nan(eve::as<T>()), 0.5);

  TTS_IEEE_EQUAL(eve__erf_inv(T( 0 )),T(0)  );
  TTS_IEEE_EQUAL(eve__erf_inv(T(-0.)), T(0) );
  TTS_ULP_EQUAL(eve__erf_inv(T( 0.1 )), T( boost::math::erf_inv(0.1)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T( 0.2 )), T( boost::math::erf_inv(0.2)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T( 0.3 )), T( boost::math::erf_inv(0.3)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T( 0.5 )), T( boost::math::erf_inv(0.5)),  1 );
  TTS_ULP_EQUAL(eve__erf_inv(T( 0.15)), T( boost::math::erf_inv(0.15)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T( 0.75)), T( boost::math::erf_inv(0.75)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T(- 0.1 )), T( boost::math::erf_inv(-0.1)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T( -0.2 )), T( boost::math::erf_inv(-0.2)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T( -0.3 )), T( boost::math::erf_inv(-0.3)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T( -0.5 )), T( boost::math::erf_inv(-0.5)),  1 );
  TTS_ULP_EQUAL(eve__erf_inv(T( -0.15)), T( boost::math::erf_inv(-0.15)), 0.5 );
  TTS_ULP_EQUAL(eve__erf_inv(T( -0.75)), T( boost::math::erf_inv(-0.75)), 0.5 );
}
