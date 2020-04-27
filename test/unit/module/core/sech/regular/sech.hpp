//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sech.hpp>
#include <eve/function/all.hpp>
#include <eve/function/rec.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::sech return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sech(T(0)), T);
}

TTS_CASE_TPL("Check eve::sech behavior", EVE_TYPE)
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sech(eve::Nan<T>()) , (eve::Nan<T>()) );
    TTS_IEEE_EQUAL(eve::sech(eve::Inf<T>()) , (T( 0 )) );
    TTS_IEEE_EQUAL(eve::sech(eve::Minf<T>()), (T( 0 )) );
    TTS_EXPECT(eve::all(eve::is_positive(eve::sech(eve::Inf<T>()))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::sech(eve::Minf<T>()))));
  }
  TTS_ULP_EQUAL(eve::sech(T(1)), T(eve::rec(std::cosh(v_t(1)))), 0.5);
  TTS_ULP_EQUAL(eve::sech(T(-1)),T(eve::rec(std::cosh(v_t(-1)))), 0.5);
  TTS_IEEE_EQUAL((eve::sech(T(0))), (T(1)));
  TTS_IEEE_EQUAL((eve::sech(T(-0.))), (T(1)));
  }
