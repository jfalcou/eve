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
auto baseg = [](auto i, auto) { return i; };
auto nextg = [](auto i, auto) { return i + 1; };

TTS_CASE_TPL( "Check self-increment on wide", EVE_TYPE )
{
  TTS_WHEN("A value is initialized")
  {
    T simd(baseg), next(nextg);
    T prev(simd), res;

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
