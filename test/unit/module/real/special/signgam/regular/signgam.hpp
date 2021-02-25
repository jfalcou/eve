//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/signgam.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::signgam return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::signgam(T(0)), T);
}

TTS_CASE_TPL("Check eve::signgam behavior", EVE_TYPE)
{
  auto eve__signgam =  [](auto x) { return eve::signgam(x); };
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__signgam(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__signgam(eve::inf(eve::as<T>()))  , eve::one(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__signgam(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_EQUAL(eve__signgam(T(0.5)), T(1) );
  TTS_IEEE_EQUAL(eve__signgam(T(-35)), eve::nan(eve::as<T>()));

  TTS_IEEE_EQUAL(eve__signgam(T( 0 )), T(1) );
  TTS_IEEE_EQUAL(eve__signgam(T(-0.)), T(-1) );
  TTS_IEEE_EQUAL(eve__signgam(T( 1 )), T(1) );
  TTS_IEEE_EQUAL(eve__signgam(T( 2 )), T(1) );
  TTS_IEEE_EQUAL(eve__signgam(T( 3 )), T(1) );
  TTS_IEEE_EQUAL(eve__signgam(T( 5 )), T(1) );
  TTS_IEEE_EQUAL(eve__signgam(T( -1.1 )), T(1) );
  TTS_IEEE_EQUAL(eve__signgam(T( -2.1 )), T(-1) );
  TTS_IEEE_EQUAL(eve__signgam(T( -3.1 )), T(1) );
  TTS_IEEE_EQUAL(eve__signgam(T( -4.1 )), T(-1) );
  TTS_IEEE_EQUAL(eve__signgam(T( -5.1 )), T(1) );
}
