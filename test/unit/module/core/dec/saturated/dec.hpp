//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/dec.hpp>
#include <eve/function/saturated.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/mzero.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::saturated_(eve::dec) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::saturated_(eve::dec)(T()), T);
}

TTS_CASE_TPL("Check eve::saturated_(eve::dec) behavior", EVE_TYPE)
{
  using eve::saturated_;

  TTS_EQUAL(saturated_(eve::dec)(eve::Valmin<T>()), eve::Valmin<T>());
  TTS_EQUAL(saturated_(eve::dec)(T(1)), (T( 0)) );
  TTS_EQUAL(saturated_(eve::dec)(T(2)), (T( 1)) );

  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(saturated_(eve::dec)(T(0)), (T(-1)) );
  }
  else
  {
    TTS_EQUAL(saturated_(eve::dec)(T(0)), (T(0)) );
  }
}
