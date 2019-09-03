//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_OR_HPP
#define BITWISE_OR_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/bitwise_or.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check bitwise_or behavior on homogeneous wide",
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
      ref([](auto i, auto c) { return eve::bitwise_or(Type(i), Type(2 * i)); });

  TTS_EQUAL(ref, eve::bitwise_or(lhs, rhs));
  TTS_EQUAL(ref, lhs | rhs);
}

TTS_CASE_TPL("Check bitwise_or behavior on wide + scalar",
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
      ref([](auto i, auto c) { return eve::bitwise_or(Type(i % 3), Type(-1)); });

  TTS_EQUAL(ref, eve::bitwise_or(lhs, Type(-1)));
  TTS_EQUAL(ref, lhs | Type(-1));
}

TTS_CASE_TPL("Check bitwise_or with mixed types",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  {
    wide<float, T>   lhs([](auto i, auto c) { return c - i; });
    wide<int32_t, T> rhs([](auto i, auto) { return i; });
    wide<float, T>   ref([](auto i, auto c) { return eve::bitwise_or(float(c - i), int32_t(i)); });

    TTS_IEEE_EQUAL(ref, eve::bitwise_or(lhs, rhs));
    TTS_IEEE_EQUAL(ref, lhs | rhs);
  }
  {
    wide<int32_t, T> lhs([](auto i, auto c) { return int32_t(i % 3); }),
        ref([](auto i, auto c) { return eve::bitwise_or(int32_t(i % 3), -3.322f); });

    TTS_IEEE_EQUAL(ref, eve::bitwise_or(lhs, -3.322f));
    TTS_IEEE_EQUAL(ref, lhs | -3.322f);
  }
}

#endif
