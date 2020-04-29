//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lerp.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>
#include <cmath>

TTS_CASE("Check eve::lerp return type")
{
  TTS_EXPR_IS(eve::raw_(eve::lerp)(EVE_TYPE(), EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::raw_(eve::lerp) behavior")
{
  for (EVE_VALUE i = -10; i <= 20; i+= 1)
  {
    auto l = i/EVE_VALUE(10);
    TTS_ULP_EQUAL(eve::raw_(eve::lerp)(EVE_TYPE(1), EVE_TYPE(2), EVE_TYPE(l)),  EVE_TYPE(std::lerp(EVE_VALUE(1), EVE_VALUE(2), l)), 0.5);
  }

    auto e0 = eve::raw_(eve::lerp)(EVE_VALUE(1), EVE_VALUE(2), eve::prev(1-10*eve::Eps<EVE_VALUE>()));
  auto s0 = std::lerp(EVE_VALUE(1), EVE_VALUE(2), eve::prev(1-10*eve::Eps<EVE_VALUE>()));
  for (EVE_VALUE i = 1-10*eve::Eps<EVE_VALUE>(); i <= 1+10*eve::Eps<EVE_VALUE>(); i =  eve::next(i))
  {
    auto e1 = eve::raw_(eve::lerp)(EVE_VALUE(1), EVE_VALUE(2), i);
    auto s1 = std::lerp(EVE_VALUE(1), EVE_VALUE(2), i);
    TTS_LESS_EQUAL(e0, e1);
    TTS_LESS_EQUAL(s0, s1);
    e0 = e1;
    s0 = s1;
  }
}
