//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check nan return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::nan(eve::as<T>()), T);
}

TTS_CASE_TPL("Check nan behavior", EVE_TYPE)
{
  TTS_IEEE_EQUAL(eve::nan(eve::as<T>()), eve::inf(eve::as<T>()) - eve::inf(eve::as<T>()));
}
