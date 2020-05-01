//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lcm.hpp>
#include <eve/constant/valmin.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <numeric>

TTS_CASE("Check eve::lcm return type")
{
  TTS_EXPR_IS(eve::lcm(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::lcm behavior")
{
  TTS_EQUAL(eve::lcm((EVE_TYPE(22)) , (EVE_TYPE(10)) ) ,  EVE_TYPE(std::lcm((EVE_VALUE(22)) , (EVE_VALUE(10)))));
  TTS_EQUAL(eve::lcm((EVE_TYPE(22)) , (EVE_TYPE(-10)) ) ,  EVE_TYPE(std::lcm((EVE_VALUE(22)) , (EVE_VALUE(-10)))));
  TTS_EQUAL(eve::lcm(eve::Valmin<EVE_TYPE>(), (EVE_TYPE(2)) ) ,  EVE_TYPE(std::lcm(eve::Valmin<EVE_VALUE>(), (EVE_VALUE(2)) )));
  TTS_EQUAL(eve::lcm(eve::Valmin<EVE_TYPE>(), (EVE_TYPE(1)) ) ,  EVE_TYPE(std::lcm(eve::Valmin<EVE_VALUE>(), (EVE_VALUE(1)) )));
  EVE_VALUE z = eve::Valmin<EVE_VALUE>()/2;
  TTS_EQUAL((eve::lcm(EVE_TYPE(z), EVE_TYPE(2)))  ,  EVE_TYPE(std::lcm(z, (EVE_VALUE(2))) ));
  TTS_EQUAL((eve::lcm(EVE_TYPE(z), EVE_TYPE(1)))  ,  EVE_TYPE(std::lcm(z, (EVE_VALUE(1))) ));
  TTS_EQUAL(eve::lcm((EVE_TYPE(0)) , (EVE_TYPE(1)) ) ,  EVE_TYPE(std::lcm((EVE_VALUE(0)) , (EVE_VALUE(1)))));
  TTS_EQUAL(eve::lcm((EVE_TYPE(1)) , (EVE_TYPE(0)) ) ,  EVE_TYPE(std::lcm((EVE_VALUE(1)) , (EVE_VALUE(0)))));

}
