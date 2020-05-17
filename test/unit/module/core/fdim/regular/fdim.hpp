//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fdim.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::fdim return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::fdim(T(), T()), T);
}

TTS_CASE_TPL(" fdim behaviour", EVE_TYPE)
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::fdim(eve::Inf<T>() , eve::Inf<T>())  , T(0));
    TTS_EQUAL(eve::fdim(eve::Minf<T>(), eve::Minf<T>()) , T(0));

    TTS_ULP_EQUAL(eve::fdim(eve::Nan<T>() , eve::Nan<T>() ), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::fdim(eve::Nan<T>() , T(0)          ), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::fdim(T(0)          , eve::Nan<T>() ), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::fdim(eve::Nan<T>() , T(0)          ), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::fdim(T(1)          , eve::Nan<T>() ), eve::Nan<T>(), 0);
    TTS_ULP_EQUAL(eve::fdim(eve::Nan<T>() , T(1)          ), eve::Nan<T>(), 0);
  }

  TTS_EQUAL(eve::fdim(T(-1), T(-1)) , T(0));
  TTS_EQUAL(eve::fdim(T( 1), T( 1)) , T(0));
  TTS_EQUAL(eve::fdim(T( 0), T( 0)) , T(0));
  TTS_EQUAL(eve::fdim(T( 1), T( 0)) , T(1));
  TTS_EQUAL(eve::fdim(T( 2), T(-3)) , T(5));
  TTS_EQUAL(eve::fdim(T( 2), T( 3)) , T(0));
}
