//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SUB_HPP
#define SUB_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/sub.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check sub behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  wide<Type, T> lhs([](auto i, auto c) { return c + i; }), rhs([](auto i, auto) { return i; }),
    ref(T::value);
  
  TTS_EQUAL(ref, eve::sub(lhs, rhs)); 
  TTS_EQUAL(ref, lhs - rhs);
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
    ref1([](auto i, auto) { return i - Type(4); }),
    ref2([](auto i, auto) { return Type(4) - i; });
  
  TTS_EQUAL(ref1, eve::sub(lhs, 4));
  TTS_EQUAL(ref2, eve::sub(4, lhs));
  
  TTS_EQUAL(ref1, lhs - 4);
  TTS_EQUAL(ref2, 4 - lhs); 
}

#endif
