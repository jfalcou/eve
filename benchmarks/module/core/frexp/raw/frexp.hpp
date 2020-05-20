//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/frexp.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check frexp return type")
{
  TTS_EXPR_IS(eve::raw_(eve::frexp)(EVE_TYPE()), (std::tuple<EVE_TYPE,EVE_TYPE>));
}

TTS_CASE("Check eve::raw_(eve::frexp) behavior")
{
  auto [p0, p1] = eve::raw_(eve::frexp)(EVE_TYPE(1));
  TTS_EQUAL(p0, EVE_TYPE(0.5));
  TTS_EQUAL(p1, EVE_TYPE(1));


}
