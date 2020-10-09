//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/digamma.hpp>
#include <boost/math/special_functions/digamma.hpp>
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

TTS_CASE_TPL("Check eve::digamma return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::digamma(T(0)), T);
}

TTS_CASE_TPL("Check eve::digamma behavior", EVE_TYPE)
{
  auto eve__digamma =  [](auto x) { return eve::digamma(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__digamma(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__digamma(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__digamma(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve__digamma(T(0.5)), T( boost::math::digamma(0.5)), 1. );
  TTS_ULP_EQUAL(eve__digamma(T(-35)), eve::nan(eve::as<T>()), 0.5);

  TTS_IEEE_EQUAL(eve__digamma(T( 0 )), eve::inf(eve::as<T>())  );
  TTS_IEEE_EQUAL(eve__digamma(T(-0.)), eve::minf(eve::as<T>()) );
  TTS_ULP_EQUAL(eve__digamma(T( 1 )), T( boost::math::digamma(1)), 0.5 );
  TTS_ULP_EQUAL(eve__digamma(T( 2 )), T( boost::math::digamma(2)), 0.5 );
  TTS_ULP_EQUAL(eve__digamma(T( 3 )), T( boost::math::digamma(3)), 0.5 );
  TTS_ULP_EQUAL(eve__digamma(T( 5 )), T( boost::math::digamma(5)),  0.5 );
  TTS_ULP_EQUAL(eve__digamma(T( 15)), T( boost::math::digamma(15)), 0.5 );
  TTS_ULP_EQUAL(eve__digamma(T( 50)), T( boost::math::digamma(50)), 0.5 );


}
