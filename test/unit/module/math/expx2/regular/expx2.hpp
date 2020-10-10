//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/expx2.hpp>
#include <eve/function/exp.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/concept/value.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/concept/value.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::expx2 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::expx2(T()), T);
}


TTS_CASE_TPL("Check eve::expx2 behavior", EVE_TYPE)
{
  using eve::as;
  TTS_ULP_EQUAL (eve::expx2(T(1)), eve::exp(T(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(T(0)), T(1));
  TTS_IEEE_EQUAL(eve::expx2(T(4)), eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(T(-4)),eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<T>())) , eve::nan(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<T>())) , eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<T>())), eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(T(-0.)), T(1));
  TTS_ULP_EQUAL (eve::expx2(T(-1)) , eve::exp(T(1)), 0.5);
}

TTS_CASE_TPL("Check eve::expx2 behavior", EVE_TYPE)
{
  using eve::as;
   TTS_ULP_EQUAL (eve::expx2(T(1), T(1)), eve::exp(T(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(T(0), T(1)), T(1));
  TTS_IEEE_EQUAL(eve::expx2(T(4), T(1)), eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(T(-4), T(1)),eve::exp(T(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<T>()), T(1)) , eve::nan(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<T>()), T(1)) , eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<T>()), T(1)), eve::inf(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(T(-0.), T(1)), T(1));
  TTS_ULP_EQUAL (eve::expx2(T(-1), T(1)) , eve::exp(T(1)), 0.5);

  TTS_ULP_EQUAL (eve::expx2(T(1), T(-1)), eve::exp(-T(1)), 0.5);
  TTS_IEEE_EQUAL(eve::expx2(T(0), T(-1)), T(1));
  TTS_IEEE_EQUAL(eve::expx2(T(4), T(-1)), eve::exp(-T(16)));
  TTS_IEEE_EQUAL(eve::expx2(T(-4), T(-1)),eve::exp(-T(16)));
  TTS_IEEE_EQUAL(eve::expx2(eve::nan(as<T>()), T(-1)) , eve::nan(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::inf(as<T>()), T(-1)) , eve::zero(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(eve::minf(as<T>()), T(-1)), eve::zero(as<T>()) );
  TTS_IEEE_EQUAL(eve::expx2(T(-0.), T(-1)), T(1));
  TTS_ULP_EQUAL (eve::expx2(T(-1), T(-1)) , eve::exp(-T(1)), 0.5);
}
