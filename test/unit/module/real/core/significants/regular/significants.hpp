//==================================================================================================
/**
  EVE - Expressive Vector Engine 
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/significants.hpp>

TTS_CASE_TPL("Check eve::round return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::significants(T(0), 1), T);
}

TTS_CASE_TPL("Check eve::significants behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::significants(T(1.234567), 1), T(1.) );
  TTS_EQUAL(eve::significants(T(1.234567), 2), T(1.2) );
  TTS_EQUAL(eve::significants(T(1.234567), 3), T(1.23) );
  TTS_EQUAL(eve::significants(T(1.234567), 4), T(1.235) );
  TTS_EQUAL(eve::significants(T(0.01234567), 1),T(0.01) );
  TTS_EQUAL(eve::significants(T(0.01234567), 2),T(0.012) );
  TTS_EQUAL(eve::significants(T(0.01234567), 3),T(0.0123) );
  TTS_EQUAL(eve::significants(T(0.01234567), 4),T(0.01235) );
}
