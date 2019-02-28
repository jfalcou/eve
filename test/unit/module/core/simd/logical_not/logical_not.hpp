//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_NOT_HPP
#define LOGICAL_NOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/logical.hpp>
#include <eve/function/simd/logical_not.hpp>
#include <eve/wide.hpp>
 
using eve::fixed;

TTS_CASE_TPL("Check logical_not behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  TTS_SETUP(" wide")
  {
    using t_t = wide<Type, T>;
    using l_t = eve::as_logical_t <t_t>; 
    t_t lhs([](int i, int) { return i%2; });
    
    l_t ref([](int i, int) { return eve::logical_not(Type(i%2)); });

    TTS_SECTION("supports eve::logical_not") { TTS_EQUAL(ref, eve::logical_not(lhs)); }
    TTS_SECTION("supports operator!") { TTS_EQUAL(ref, !lhs); }
  } 
}

TTS_CASE_TPL("Check logical_not behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  TTS_SETUP(" wide logical")
  {
    using t_t = wide<Type, T>;
    using l_t = eve::as_logical_t <t_t>; 
    l_t lhs([](int i, int) { return i%2 == 0; });
    
    l_t ref([](int i, int) { return eve::logical_not(i%2 == 0); });

    TTS_SECTION("supports eve::logical_not") { TTS_EQUAL(ref, eve::logical_not(lhs)); }
    TTS_SECTION("supports operator!") { TTS_EQUAL(ref, !lhs); }
  } 
}
 

#endif
