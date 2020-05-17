//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_infinite.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::is_infinite return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_infinite(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_infinite behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_infinite(T(0)), eve::False<T>() );
  TTS_EQUAL(eve::is_infinite(T(2)), eve::False<T>() );

  if constexpr(eve::floating_value<T> && eve::platform::supports_infinites)
  {
    TTS_EQUAL(eve::is_infinite(eve::Inf<T>())  , eve::True<T>());
    TTS_EQUAL(eve::is_infinite(eve::Minf<T>()) , eve::True<T>());
  }

  if constexpr(eve::floating_value<T> && eve::platform::supports_nans)
  {
    TTS_EQUAL(eve::is_infinite(eve::Nan<T>()), eve::False<T>());
  }
}
