//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/epsilon.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/eps.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::epsilon return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::epsilon(T(0)), T);
}

TTS_CASE_TPL("Check eve::epsilon behavior", EVE_TYPE)
{
  using eve::as;
  if constexpr(eve::floating_value<T>)
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_ULP_EQUAL(eve::epsilon(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::epsilon(eve::inf(eve::as<T>())),  eve::nan(eve::as<T>()), 0);
      TTS_ULP_EQUAL(eve::epsilon(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    }
    TTS_ULP_EQUAL(eve::epsilon(T(1)), eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(0)), eve::mindenormal(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(10)), 8*eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(5)),  4*eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(2)),  2*eve::eps(as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(1.5)),  eve::eps(as<T>()), 0.5);
  }
  else
  {
    TTS_ULP_EQUAL(eve::epsilon(T(1)), T(1), 0.5);
    TTS_ULP_EQUAL(eve::epsilon(T(10)), T(10), 0.5);
  }
}
