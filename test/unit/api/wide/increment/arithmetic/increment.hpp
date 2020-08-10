//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/wide.hpp>

// Generator for the base values
auto baseg = [](auto i, auto) { return i; };
auto nextg = [](auto i, auto) { return i + 1; };

TTS_CASE_TPL("Check self-decrement on wide"
            , eve::fixed<1>
            , eve::fixed<2>
            , eve::fixed<4>
            , eve::fixed<8>
            , eve::fixed<16>
            , eve::fixed<32>
            , eve::fixed<64>
            )
{
  TTS_WHEN("A value is initialized")
  {
    eve::wide<EVE_TYPE, T> simd(baseg), next(nextg);
    eve::wide<EVE_TYPE, T> prev(simd), res;

    TTS_AND_THEN("We call post-decrement operator on the value")
    {
      res = simd++;
      TTS_EQUAL(simd, next);
      TTS_EQUAL(res , prev);
    }

    TTS_AND_THEN("We call pre-decrement operator on the value")
    {
      res = ++simd;
      TTS_EQUAL(simd, next);
      TTS_EQUAL(res , next);
    }
  }
}
