//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/logical_not.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>

TTS_CASE_TPL("Check logical_not return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::logical_not(T())               , eve::logical<T>);
  TTS_EXPR_IS(eve::logical_not(eve::logical<T>()) , eve::logical<T>);
}

TTS_CASE_TPL("Check eve::logical_not behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::logical_not(T(1))             , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_not(T(0))             , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::logical_not(eve::allbits(eve::as<T>())), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_not(eve::true_(eve::as<T>()))   , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::logical_not(eve::false_(eve::as<T>()))  , eve::true_(eve::as<T>()) );
}

TTS_CASE_TPL("Check eve::operator! behavior", EVE_TYPE)
{
  TTS_EQUAL(!eve::true_(eve::as<T>())  , eve::false_(eve::as<T>()));
  TTS_EQUAL(!eve::false_(eve::as<T>()) , eve::true_(eve::as<T>()));
}
