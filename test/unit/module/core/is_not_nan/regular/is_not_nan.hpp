//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_nan.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_not_nan return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_nan(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_not_nan behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_not_nan(T(0)), eve::True<T>());
  TTS_EQUAL(eve::is_not_nan(T(2)), eve::True<T>());

  if constexpr(eve::floating_value<T> && eve::platform::supports_nans)
  {
    TTS_EQUAL(eve::is_not_nan(eve::Nan<T>()), eve::False<T>());
  }
}
