//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_negative.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_negative return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_negative(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_negative behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_negative(T(0)), eve::False<T>());
  TTS_EQUAL(eve::is_negative(T(2)), eve::False<T>());

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_negative(T(-1)), eve::True<T>());
  }
  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_negative(T( 0 )), eve::False<T>() );
    TTS_EQUAL(eve::is_negative(T(-0.)), eve::True<T>()  );

    if constexpr(eve::platform::supports_nans)
    {
      TTS_EQUAL(eve::is_negative(eve::Nan<T>()), eve::True<T>());
    }
  }
}
