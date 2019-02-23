//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_ANDNOT_HPP
#define BITWISE_ANDNOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/bitwise_andnot.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL( "Check bitwise_andnot behavior on homogeneous wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return c-i; })
                , rhs([](int i, int  ) { return i+1; })
                , ref([](int i, int c) { return eve::bitwise_andnot(Type(c-i),Type(i+1)); });

    TTS_SECTION( "supports eve::bitwise_andnot" )  { TTS_EQUAL(ref, eve::bitwise_andnot(lhs,rhs)); }
  }
}

TTS_CASE_TPL( "Check bitwise_andnot behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return i%3; })
                , ref([](int i, int c) { return eve::bitwise_andnot( Type(i%3), Type(7) ); });

    TTS_SECTION( "supports eve::bitwise_andnot" )  { TTS_EQUAL(ref, eve::bitwise_andnot(lhs,7)); }
  }
}

#endif
