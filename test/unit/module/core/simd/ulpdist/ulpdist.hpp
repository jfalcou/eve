//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ULPDIST_HPP
#define ULPDIST_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/ulpdist.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check plus behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return c - i; }),
      ref([](auto i, auto c) { return eve::ulpdist(Type(i), Type(c - i)); });

  TTS_EQUAL(ref, eve::ulpdist(lhs, rhs));
}

TTS_CASE_TPL("Check plus behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto) { return i; }),
      ref([](auto i, auto) { return eve::ulpdist(Type(i), Type(2)); });

  TTS_EQUAL(ref, eve::ulpdist(lhs, Type(2)));
  TTS_EQUAL(ref, eve::ulpdist(Type(2), lhs));
}

#endif
