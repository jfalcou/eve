//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sindcosd.hpp>
#include <eve/function/sind.hpp>
#include <eve/function/cosd.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <type_traits>
#include <utility>
#include <cmath>

TTS_CASE("Check sindcosd  return type")
{
  TTS_EXPR_IS((eve::restricted_(eve::sindcosd)(EVE_TYPE())), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check (eve::sindcosd behavior")
{
  static const int N = 6;
  const EVE_VALUE _180 = EVE_VALUE(180);
  EVE_VALUE x[N] = {   _180/8, -_180/8
                   , _180/4, -_180/4
                       , _180, -_180};

  for(int i=0; i < 4 ; ++i)
  {
    auto [p0, p1] = eve::restricted_(eve::sindcosd)(EVE_TYPE(x[i]));
    TTS_ULP_EQUAL(p0, EVE_TYPE(eve::restricted_(eve::sind)(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, EVE_TYPE(eve::restricted_(eve::cosd)(x[i])), 0.5);
  }
  for(int i=4; i < 6 ; ++i)
  {
    auto [p0, p1] = eve::restricted_(eve::sindcosd)(EVE_TYPE(x[i]));
    TTS_ULP_EQUAL(p0, eve::Nan<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(p1, eve::Nan<EVE_TYPE>(), 0.5);
  }
}
