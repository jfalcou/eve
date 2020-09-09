//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_mask.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::bit_mask return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::bit_mask(T()), T);
}

TTS_CASE_TPL("Check eve::bit_mask behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::bit_mask( T(0))           , T(0));
  TTS_EQUAL(eve::bit_mask(-T(0))           , T(0));
  TTS_EQUAL(eve::bit_mask(eve::False<T>()) , T(0));

  TTS_IEEE_EQUAL(eve::bit_mask(T(1))           , (eve::allbits(eve::as<T>())));
  TTS_IEEE_EQUAL(eve::bit_mask(eve::True<T>()) , (eve::allbits(eve::as<T>())));
}
