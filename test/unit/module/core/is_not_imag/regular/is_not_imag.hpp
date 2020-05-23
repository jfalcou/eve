//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_not_imag.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_not_imag return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_not_imag(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_not_imag behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_not_imag(T(0)), eve::False<T>() );
  TTS_EQUAL(eve::is_not_imag(T(2)), eve::True<T>()  );
}
