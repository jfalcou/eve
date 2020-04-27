//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rec.hpp>
#include <eve/function/raw.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::raw_(eve::raw_(eve::rec)) return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::raw_(eve::rec)(T(0)), T);
}

TTS_CASE_TPL("Check eve::raw_(eve::rec) behavior", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    TTS_RELATIVE_EQUAL(eve::raw_(eve::rec)( T(1)) , (T(1))     , 0.2);
    TTS_RELATIVE_EQUAL(eve::raw_(eve::rec)( T(47)), (T(1./47.)), 0.2);
  }
  else
  {
    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL(eve::raw_(eve::rec)(T(- 1)), (T(-1)));
      TTS_EQUAL(eve::raw_(eve::rec)(T(-47)), (T( 0)));
    }
    else
    {
      TTS_EQUAL(eve::raw_(eve::rec)(T(1)) , (T(1)));
      TTS_EQUAL(eve::raw_(eve::rec)(T(47)), (T(0)));
    }
  }
}
