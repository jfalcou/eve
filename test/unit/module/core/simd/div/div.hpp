//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DIV_HPP
#define DIV_HPP

#include "test.hpp"
#include <tts/tests/precision.hpp>
#include <eve/function/div.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check div behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

    wide<Type, T> lhs([](auto i, auto c) { return c; }),
                  rhs([](auto i, auto ) { return 1 + i; }),
                  ref([](auto i, auto c) { return Type(c)/(1 + i); });

    TTS_ULP_EQUAL(ref, eve::div(lhs, rhs),0.5);
    TTS_ULP_EQUAL(ref, lhs / rhs,0.5);
}

TTS_CASE_TPL("Check div behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto) { return i+1; }),
                rref([](auto i, auto) { return (1+i) / Type(4); }),
                lref([](auto i, auto) { return Type(4) / (i+1); });

  TTS_ULP_EQUAL(lref, eve::div(4, lhs),0.5);
  TTS_ULP_EQUAL(rref, eve::div(lhs, 4),0.5);

  TTS_ULP_EQUAL(lref, 4 / lhs,0.5);
  TTS_ULP_EQUAL(rref, lhs / 4,0.5);
}

#endif
