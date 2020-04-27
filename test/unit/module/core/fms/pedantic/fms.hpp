//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE_TPL("Check eve::fms return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::pedantic_(eve::fms)(T(), T(), T()), T);
}

TTS_CASE_TPL("Check eve::pedantic_(eve::fms) behavior", EVE_TYPE)
{
  TTS_EQUAL(eve::pedantic_(eve::fms)(T(0), T(0), T(0)), (T(0)));
  TTS_EQUAL(eve::pedantic_(eve::fms)(T(0), T(0), T(-7)), (T(7)));
  TTS_EQUAL(eve::pedantic_(eve::fms)(T(2), T(0), T(-7)), (T(7)));
  TTS_EQUAL(eve::pedantic_(eve::fms)(T(0), T(5), T(-7)), (T(7)));
  TTS_EQUAL(eve::pedantic_(eve::fms)(T(2), T(5), T(-7)), (T(17)));
  if constexpr(eve::floating_value<T>)
  {
    T e = eve::Eps<T>();
    TTS_EQUAL(eve::pedantic_(eve::fms)(eve::inc(e), eve::oneminus(e), eve::One<T>()), (-eve::sqr(e)));
  }
}
