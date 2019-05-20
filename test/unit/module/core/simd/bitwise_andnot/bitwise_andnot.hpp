//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

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
  wide<Type,T>  lhs([](auto i, auto c) { return c-i; })
    , rhs([](auto i, auto  ) { return i+1; })
    , ref([](auto i, auto c) { return eve::bitwise_andnot(Type(c-i),Type(i+1)); });
  
  TTS_EQUAL(ref, eve::bitwise_andnot(lhs,rhs)); 
}

TTS_CASE_TPL( "Check bitwise_andnot behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  
  wide<Type,T>  lhs([](auto i, auto c) { return Type(i%3); })
    , ref([](auto i, auto c) { return eve::bitwise_andnot( Type(i%3), Type(7) ); });
  
  TTS_EQUAL(ref, eve::bitwise_andnot(lhs,7)); 
}

#endif
