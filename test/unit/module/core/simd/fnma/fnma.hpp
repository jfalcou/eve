//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FNMA_HPP
#define FNMA_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check fnma behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> arg0([](auto i, auto) { return Type(i); }),
      arg1([](auto i, auto c) { return Type(c); }),
      arg2([](auto i, auto c) { return Type(c - i); }),
      ref([](auto i, auto c) { return -Type(i * c) + (c - i); });

  TTS_EQUAL(ref, eve::fnma(arg0, arg1, arg2));
}

TTS_CASE_TPL("Check fnma behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> arg0([](auto i, auto) { return Type(i); }),
      arg1([](auto i, auto c) { return Type(c); }),
      arg2([](auto i, auto c) { return Type(c - i); }),
      refvvs([](auto i, auto c) { return -Type(i) * Type(c) + Type(4); }),
      refvss([](auto i, auto c) { return -Type(i) * Type(10) + Type(4); }),
      refvsv([](auto i, auto c) { return Type(-i) * Type(10) + (c - i); }),
      refsvs([](auto i, auto c) { return Type(-5) * Type(c) + Type(4); }),
      refssv([](auto i, auto c) { return Type(-5) * Type(10) + Type(c - i); }),
      refsvv([](auto i, auto c) { return Type(-5) * Type(c) + Type(c - i); });

  TTS_EQUAL(refvvs, eve::fnma(arg0, arg1, 4));
  TTS_EQUAL(refvss, eve::fnma(arg0, 10, 4));
  TTS_EQUAL(refvsv, eve::fnma(arg0, 10, arg2));
  TTS_EQUAL(refsvs, eve::fnma(5, arg1, 4));
  TTS_EQUAL(refssv, eve::fnma(5, 10, arg2));
  TTS_EQUAL(refsvv, eve::fnma(5, arg1, arg2));
}

#endif
