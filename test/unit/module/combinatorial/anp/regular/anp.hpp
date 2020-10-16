//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/anp.hpp>
#include <eve/platform.hpp>
#include <eve/concept/value.hpp>

TTS_CASE_TPL("Check eve::anp return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::anp(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::anp behavior", EVE_TYPE)
{

  auto eve__anp =  [](auto n, auto p) { return eve::anp(n, p); };

  if constexpr( eve::floating_value<T> )
  {
    TTS_ULP_EQUAL(eve__anp(T(2), eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__anp(T(2), eve::inf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(eve__anp(T(3), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
   }

  TTS_ULP_EQUAL(eve__anp(T(10), T(5)), T(30240), 0);
  TTS_ULP_EQUAL(eve__anp(T(6), T(2)), T(30), 0);
  TTS_ULP_EQUAL(eve__anp(T(6), T(1)), T(6), 0);
  TTS_ULP_EQUAL(eve__anp(T(1), T(0)), T(1), 0);
}
