//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapresté
  
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_AND_HPP
#define BITWISE_AND_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/complement.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL( "Check complement behavior on homogeneous wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i,  int) { return i+1; })
                , ref([](int i,  int) { return eve::complement(Type(i+1)); });


    TTS_SECTION( "supports eve::complement" )  { TTS_EQUAL(ref, eve::complement(lhs)); }
    TTS_SECTION( "supports operator~" )        { TTS_EQUAL(ref, ~lhs); }
  }
}

#endif
