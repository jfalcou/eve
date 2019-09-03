//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FMA_HPP
#define FMA_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/fma.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check fma behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> arg0([](auto i, auto) { return i; }), arg1([](auto i, auto c) { return c; }),
      arg2([](auto i, auto c) { return c - i; }),
      ref([](auto i, auto c) { return i * c + (c - i); });

  TTS_EQUAL(ref, eve::fma(arg0, arg1, arg2));
}

TTS_CASE_TPL("Check fma behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> arg0([](auto i, auto) { return i; }), arg1([](auto i, auto c) { return c; }),
      arg2([](auto i, auto c) { return c - i; }), refvvs([](auto i, auto c) { return i * c + 4; }),
      refvss([](auto i, auto c) { return i * 10 + 4; }),
      refvsv([](auto i, auto c) { return i * 10 + (c - i); }),
      refsvs([](auto i, auto c) { return 5 * c + 4; }),
      refssv([](auto i, auto c) { return 5 * 10 + (c - i); }),
      refsvv([](auto i, auto c) { return 5 * c + (c - i); });

  TTS_EQUAL(refvvs, eve::fma(arg0, arg1, 4));
  TTS_EQUAL(refvss, eve::fma(arg0, 10, 4));
  TTS_EQUAL(refvsv, eve::fma(arg0, 10, arg2));
  TTS_EQUAL(refsvs, eve::fma(5, arg1, 4));
  TTS_EQUAL(refssv, eve::fma(5, 10, arg2));
  TTS_EQUAL(refsvv, eve::fma(5, arg1, arg2));
}

#endif
