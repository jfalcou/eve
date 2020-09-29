//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/gammaln.hpp>
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

TTS_CASE_TPL("Check eve::gammaln return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::gammaln(T(0)), T);
}

TTS_CASE_TPL("Check eve::gammaln behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto eve__gammaln =  [](auto x) { return eve::gammaln(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__gammaln(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__gammaln(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__gammaln(eve::minf(eve::as<T>())) , eve::inf(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve__gammaln(T(0.5)), T(std::lgamma(v_t(0.5))), 1. );
  TTS_ULP_EQUAL(eve__gammaln(T(-35)), T(std::lgamma(v_t(-35))), 0.5);

  TTS_IEEE_EQUAL(eve__gammaln(T( 0 )), eve::inf(eve::as<T>())  );
  TTS_IEEE_EQUAL(eve__gammaln(T(-0.)), eve::inf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve__gammaln(T( 1 )), T(0)           );
  TTS_IEEE_EQUAL(eve__gammaln(T( 2 )), T(0)           );
  TTS_IEEE_EQUAL(eve__gammaln(T( 3 )), T(std::log(2.0))  );
  TTS_IEEE_EQUAL(eve__gammaln(T( 5 )), T(std::log(24.0)) );
}
