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
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE_TPL("Check eve::fnma return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::numeric_(eve::fnma)(T(), T(), T()), T);
}

TTS_CASE_TPL("Check eve::numeric_(eve::fnma) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::numeric_(eve::fnma)(T(0), T(0), T(0)), (T(0)));
  TTS_EQUAL(eve::numeric_(eve::fnma)(T(0), T(0), T(7)), (T(7)));
  TTS_EQUAL(eve::numeric_(eve::fnma)(T(2), T(0), T(7)), (T(7)));
  TTS_EQUAL(eve::numeric_(eve::fnma)(T(0), T(5), T(7)), (T(7)));
  TTS_EQUAL(eve::numeric_(eve::fnma)(T(-2), T(5), T(7)), (T(17)));
  if constexpr(eve::floating_value<T>)
  {
    T e = eve::Eps<T>();
    TTS_EQUAL(eve::numeric_(eve::fnma)(eve::inc(e), eve::oneminus(e), eve::One<T>()), (eve::sqr(e)));
    TTS_EQUAL(eve::numeric_(eve::fnma)(eve::Valmax<T>(), T(2), eve::Valmax<T>()), -eve::Valmax<T>());
  }

}
