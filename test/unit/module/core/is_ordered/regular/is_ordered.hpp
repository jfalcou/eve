//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_ordered.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check is_ordered return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_ordered(T(), T()), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_ordered behavior on arithmetic", EVE_TYPE)
{
  TTS_EQUAL(eve::is_ordered(T(1), T(1)), eve::True<T>());
  TTS_EQUAL(eve::is_ordered(T(3), T(1)), eve::True<T>());
  TTS_EQUAL(eve::is_ordered(T(1), T(3)), eve::True<T>());

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_ordered(eve::nan(eve::as<T>()), T(3)), eve::False<T>());
    TTS_EQUAL(eve::is_ordered(T(3), eve::nan(eve::as<T>())), eve::False<T>());
    TTS_EQUAL(eve::is_ordered(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())), eve::False<T>());
  }
}
