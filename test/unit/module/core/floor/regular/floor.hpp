//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/floor.hpp>

TTS_CASE_TPL("Check eve::floor return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::floor(T()), T);
}

TTS_CASE_TPL("Check eve::floor behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::floor(T(0)), T(0));
  TTS_EQUAL(eve::floor(T(1)), T(1));
  TTS_EQUAL(eve::floor(T(2)), T(2));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::floor(static_cast<T>(-1)), T(-1));
    TTS_EQUAL(eve::floor(static_cast<T>(-2)), T(-2));
  }

  if constexpr(eve::floating_value<T>)
  {
   TTS_EQUAL(eve::floor(static_cast<T>(-1.3)), T(-2));
   TTS_EQUAL(eve::floor(static_cast<T>(-1.5)), T(-2));
   TTS_EQUAL(eve::floor(static_cast<T>(-1.6)), T(-2));
   TTS_EQUAL(eve::floor(static_cast<T>(1.3)) , T( 1));
   TTS_EQUAL(eve::floor(static_cast<T>(1.5)) , T( 1));
   TTS_EQUAL(eve::floor(static_cast<T>(1.6)) , T( 1));
  }
}
