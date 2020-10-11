//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sqr_abs.hpp>


TTS_CASE_TPL("Check eve::sqr_abs return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::sqr_abs(T(0)), T);
}

TTS_CASE_TPL("Check eve::sqr_abs behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::sqr_abs(T(1))              , T(1) );
  TTS_EQUAL(eve::sqr_abs(T(2))              , T(4) );
  TTS_EQUAL(eve::sqr_abs(T(-0.))            , T(0) );
  TTS_EQUAL(eve::sqr_abs(static_cast<T>(-2)), T(4) );
}
