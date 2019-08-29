//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_XOR_HPP
#define BITWISE_XOR_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/bitwise_xor.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check bitwise_xor behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto c) { return i; }), rhs([](auto i, auto) { return 2 * i; }),
    ref([](auto i, auto c) { return eve::bitwise_xor(Type(i), Type(2 * i)); });

  TTS_EQUAL(ref, eve::bitwise_xor(lhs, rhs));
  TTS_EQUAL(ref, lhs ^ rhs);
}

TTS_CASE_TPL("Check bitwise_xor behavior on wide + scalar",
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
    ref([](auto i, auto c) { return eve::bitwise_xor(Type(i % 3), Type(-1)); });

  TTS_EQUAL(ref, eve::bitwise_xor(lhs, -1));
  TTS_EQUAL(ref, lhs ^ -1);

}

#endif

