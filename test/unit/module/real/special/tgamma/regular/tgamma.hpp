//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tgamma.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::tgamma return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::tgamma(T(0)), T);
}

TTS_CASE_TPL("Check eve::tgamma behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  auto eve__tgamma =  [](auto x) { return eve::tgamma(x); };

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve__tgamma(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__tgamma(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve__tgamma(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }

  TTS_ULP_EQUAL(eve__tgamma(T(0.5)), T(std::tgamma(v_t(0.5))), 1. );
  TTS_ULP_EQUAL(eve__tgamma(T(-35)), T(std::tgamma(v_t(-35))), 0.5);

  TTS_IEEE_EQUAL(eve__tgamma(T( 0 )), eve::inf(eve::as<T>())  );
  TTS_IEEE_EQUAL(eve__tgamma(T(-0.)), eve::minf(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve__tgamma(T( 1 )), T(1)           );
  TTS_IEEE_EQUAL(eve__tgamma(T( 2 )), T(1)           );
  TTS_IEEE_EQUAL(eve__tgamma(T( 3 )), T(2)           );
  TTS_IEEE_EQUAL(eve__tgamma(T( 5 )), T(24)          );
}
