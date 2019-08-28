//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MIN_HPP
#define MIN_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/min.hpp>
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
    ref([](auto i, auto c) { return eve::min(Type(i), Type(c - i)); });
  
  TTS_EQUAL(ref, eve::min(lhs, rhs)); 
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
    ref([](auto i, auto) { return eve::min(Type(i), Type(2)); });
  
  TTS_EQUAL(ref, eve::min(lhs, Type(2))); 
  TTS_EQUAL(ref, eve::min(Type(2), lhs)); 
}

#endif
