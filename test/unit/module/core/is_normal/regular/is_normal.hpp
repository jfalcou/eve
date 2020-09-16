//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_normal.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/smallestposval.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_normal return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_normal(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_normal behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_normal(T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_normal(T(2)), eve::true_(eve::as<T>()));

  if constexpr(eve::platform::supports_denormals && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_normal(eve::smallestposval(eve::as<T>()) / 2), eve::false_(eve::as<T>()));
  }
}
