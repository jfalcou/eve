//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/pi.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/radinpi.hpp>

#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::radinpi return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::radinpi(T()), T);
}

TTS_CASE_TPL("Check eve::radinpi behavior", EVE_TYPE)
{
  TTS_ULP_EQUAL(eve::radinpi(-eve::pi(eve::as<T>()))     , -T(1)     , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(-eve::pi(eve::as<T>())/3)   , -T(1./3.) , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(-eve::pio_2(eve::as<T>()))  , -T(0.5)   , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(-eve::pio_4(eve::as<T>()))  , -T(0.25)  , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(T(0))              ,  T(0)     , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(eve::pio_4(eve::as<T>()))   ,  T(0.25)  , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(eve::pio_2(eve::as<T>()))   ,  T(0.5)   , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(eve::pi(eve::as<T>()) / 3)  ,  T(1./3.) , 0.5 );
  TTS_ULP_EQUAL(eve::radinpi(eve::pi(eve::as<T>()))      ,  T(1)     , 0.5 );
}
