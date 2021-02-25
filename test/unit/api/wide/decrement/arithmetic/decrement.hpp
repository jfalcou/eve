//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/wide.hpp>

// Generator for the base values
auto baseg = [](auto i, auto) { return i + 1; };
auto nextg = [](auto i, auto) { return i; };

TTS_CASE_TPL("Check self-decrement on wide", EVE_TYPE)
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
