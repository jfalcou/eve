//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_even.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::is_even return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_even(T(0)), (eve::logical<T>));
}

TTS_CASE_TPL("Check eve::is_even behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_even(T(1)), eve::False<T>() );
  TTS_EQUAL(eve::is_even(T(2)), eve::True<T>()  );

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_even(T(0.5))         , eve::False<T>());
    TTS_EQUAL(eve::is_even(T(-0.)), eve::True<T>() );
  }
}
