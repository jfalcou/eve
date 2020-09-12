//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_nez.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::is_nez return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_nez(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_nez behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_nez(T(0)), eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::is_nez(T(2)), eve::true_(eve::as<T>()) );

  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::is_nez(T(-0.)), eve::false_(eve::as<T>()) );
  }
}
