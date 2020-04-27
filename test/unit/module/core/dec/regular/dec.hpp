//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::dec return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::dec(T(), T()), T);
}

TTS_CASE_TPL("Check eve::dec behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::dec(T(0)), (T(-1)) );
  TTS_EQUAL(eve::dec(T(1)), (T( 0)) );
  TTS_EQUAL(eve::dec(T(2)), (T( 1)) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::dec(T(-2)), (T(-3)));
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::dec(T(-0.)), (T(-1)));
  }
}
