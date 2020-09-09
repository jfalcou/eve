//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_ltz.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_ltz return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_ltz(T() ), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_ltz behavior", EVE_TYPE)
{
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::is_ltz(T(-1)), eve::True<T>());
  }

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_ltz(eve::nan(eve::as<T>())), eve::False<T>());
  }

  TTS_EQUAL(eve::is_ltz(T(0)), eve::False<T>());
  TTS_EQUAL(eve::is_ltz(T(3)), eve::False<T>());
}
