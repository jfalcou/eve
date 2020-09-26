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
auto baseg = [](auto i, auto) { return i + 1; };
auto nextg = [](auto i, auto) { return i; };

TTS_CASE("Check self-decrement on wide")
{
  TTS_WHEN("A value is initialized")
  {
    T simd(baseg), next(nextg);
    T prev(simd), res;

    TTS_AND_THEN("We call post-decrement operator on the value")
    {
      res = simd--;
      TTS_EQUAL(simd, next);
      TTS_EQUAL(res , prev);
    }

    TTS_AND_THEN("We call pre-decrement operator on the value")
    {
      res = --simd;
      TTS_EQUAL(simd, next);
      TTS_EQUAL(res , next);
    }
  }
}
