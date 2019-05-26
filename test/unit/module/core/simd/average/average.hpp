//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/average.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check average behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  wide<Type, T> lhs([](auto i, auto c) { return c - i; }), rhs([](auto i, auto) { return i; }),
    ref([](auto i, auto c) { return eve::average(Type(c - i), Type(i)); });
  
  TTS_EQUAL(ref, eve::average(lhs, rhs)); 
}

TTS_CASE_TPL("Check average behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto c) { return i % 3; }),
    ref([](auto i, auto c) { return eve::average(Type(i % 3), Type(7)); });
  
  TTS_EQUAL(ref, eve::average(lhs, 7));
}

#endif
