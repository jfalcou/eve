//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_finite.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::is_finite return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::is_finite(T(0)), eve::logical<T>);
}

TTS_CASE_TPL("Check eve::is_finite behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::is_finite(T(0)), eve::True<T>() );
  TTS_EQUAL(eve::is_finite(T(2)), eve::True<T>() );

  if constexpr(eve::floating_value<T>)
  {
    TTS_EQUAL(eve::is_finite(eve::inf(eve::as<T>())) , eve::False(eve::as<T>()));
    TTS_EQUAL(eve::is_finite(eve::minf(eve::as<T>())), eve::False(eve::as<T>()));
    TTS_EQUAL(eve::is_finite(eve::nan(eve::as<T>())) , eve::False(eve::as<T>()));
  }
}
