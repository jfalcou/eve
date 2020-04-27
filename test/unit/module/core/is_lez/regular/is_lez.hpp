//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_lez.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_lez return type", EVE_TYPE)
{
  using eve::logical;

  TTS_EXPR_IS(eve::is_lez(T() ), (logical<T>));
}

TTS_CASE_TPL("Check eve::is_lez behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_lez(T(-1)), eve::True<T>());
  }

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_lez(eve::Nan<T>()), eve::False<T>());
  }

  TTS_EQUAL(eve::is_lez(T(0)), eve::True<T>());
  TTS_EQUAL(eve::is_lez(T(3)), eve::False<T>());
}
