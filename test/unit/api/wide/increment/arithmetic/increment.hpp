//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/wide.hpp>

// Generator for the base values
auto baseg = [](auto i, auto) { return i; };
auto nextg = [](auto i, auto) { return i + 1; };

TTS_CASE( "Check self-increment on wide" )
{
  TTS_WHEN("A value is initialized")
  {
    EVE_TYPE simd(baseg), next(nextg);
    EVE_TYPE prev(simd), res;

    TTS_AND_THEN("We call post-increment operator on the value")
    {
      res = simd++;
      TTS_EQUAL(simd, next);
      TTS_EQUAL(res , prev);
    }

    TTS_AND_THEN("We call pre-increment operator on the value")
    {
      res = ++simd;
      TTS_EQUAL(simd, next);
      TTS_EQUAL(res , next);
    }
  }
}
