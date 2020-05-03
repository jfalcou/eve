//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/negatenz.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::negatenz return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::negatenz(T(), T()), T);
}

TTS_CASE_TPL(" negatenz behaviour", EVE_TYPE)
{
  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(eve::negatenz(eve::Inf<T>(), eve::Inf<T>()), eve::Inf<T>());
      TTS_EQUAL(eve::negatenz(eve::Minf<T>(), eve::Minf<T>()), eve::Inf<T>());

      TTS_IEEE_EQUAL( eve::negatenz(eve::Nan<T>() , eve::Nan<T>()), eve::Nan<T>() );
      TTS_IEEE_EQUAL( eve::negatenz(eve::Nan<T>() , T(0))         , eve::Nan<T>() );
    }

    TTS_EQUAL(eve::negatenz(T(1), T(-0.)) , T(-1));
    TTS_EQUAL(eve::negatenz(T(2), T(-3))  , T(-2));
    TTS_EQUAL(eve::negatenz(T(2), T( 3))  , T( 2));
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::negatenz(T(-1), T(-1)), T( 1));
    TTS_EQUAL(eve::negatenz(T(-1), T( 1)), T(-1));
  }
  TTS_EQUAL(eve::negatenz(T(1), T(1)), T(1));
  TTS_EQUAL(eve::negatenz(T(0), T(0)), T(0));
  TTS_EQUAL(eve::negatenz(T(1), T(0)), T(1));
}

