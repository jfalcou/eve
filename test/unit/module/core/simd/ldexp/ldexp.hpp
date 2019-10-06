//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef PLUS_HPP
#define PLUS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/ldexp.hpp>
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
  
  wide<Type, T> lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return Type(i); }),
    ref([](auto i, auto) { return  eve::ldexp(Type(i), Type(i)); });
  TTS_EQUAL(ref, eve::ldexp(lhs, rhs)); 
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
      ref([](auto i, auto) { return  eve::ldexp(Type(i), 4); });

    TTS_EQUAL(ref, eve::ldexp(lhs, 4)); 
}

#endif
