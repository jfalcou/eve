//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frac.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::frac return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::frac(T()), T);
}

TTS_CASE_TPL("Check eve::frac behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::frac(T(0)), T(0));
  TTS_EQUAL(eve::frac(T(2)), T(0));

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::frac(static_cast<T>(-2)), T(0) );
    TTS_EQUAL(eve::frac(static_cast<T>(1)) , T(0) );
  }

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::frac(T(-3/2.)), T(-0.5));
    TTS_EQUAL(eve::frac(T( 3/2.)), T( 0.5));

    TTS_ULP_EQUAL(eve::frac(T( 4/3.)), T( 1/3.), 0.5);
    TTS_ULP_EQUAL(eve::frac(T(-4/3.)), T(-1/3.), 0.5);
    TTS_EXPECT(eve::all(eve::is_negative(eve::frac(T(-0.0)))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::frac(T(0.0)))));
  }
}
