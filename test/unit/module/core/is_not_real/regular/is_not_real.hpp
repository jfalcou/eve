//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/is_not_real.hpp>
#include <eve/traits/as_logical.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check is_not_real return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_real(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_not_real behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_not_real(T{0}), eve::False(eve::as<T>()));
  TTS_EQUAL(eve::is_not_real(T{2}), eve::False(eve::as<T>()));
}
