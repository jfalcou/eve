//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fnma.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE_TPL("Check eve::fnma return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic_(eve::fnma)(T(), T(), T()), T);
}

TTS_CASE_TPL("Check eve::pedantic_(eve::fnma) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::pedantic_(eve::fnma)(T(0), T(0), T(0)), (T(0)));
  TTS_EQUAL(eve::pedantic_(eve::fnma)(T(0), T(0), T(7)), (T(7)));
  TTS_EQUAL(eve::pedantic_(eve::fnma)(T(2), T(0), T(7)), (T(7)));
  TTS_EQUAL(eve::pedantic_(eve::fnma)(T(0), T(5), T(7)), (T(7)));
  TTS_EQUAL(eve::pedantic_(eve::fnma)(T(-2), T(5), T(7)), (T(17)));
  if constexpr(eve::floating_value<T>)
  {
    T e = eve::Eps<T>();
    TTS_EQUAL(eve::pedantic_(eve::fnma)(eve::inc(e), eve::dec(e), eve::Mone<T>()), (-eve::sqr(e)));
  }

}
