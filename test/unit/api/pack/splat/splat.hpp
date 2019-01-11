//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SPLAT_HPP
#define SPLAT_HPP

#include <eve/pack.hpp>
#include <eve/logical.hpp>
#include <tts/tts.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::fixed;

TTS_CASE_TPL( "Check splatting constructor for pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;

  Type base = 42;
  pack<Type,T> simd( base );

  TTS_EXPECT( std::all_of(simd.begin(), simd.end(), [=](auto e) { return e == base; }) );
}

TTS_CASE_TPL( "Check splatting constructor for pack<logical>"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;
  using eve::logical;

  {
    pack<logical<Type>,T> simd( true );
    TTS_EXPECT( std::all_of(simd.begin(), simd.end(), [](auto e) { return e == true; }) );
  }

  {
    pack<logical<Type>,T> simd( false );
    TTS_EXPECT( std::all_of(simd.begin(), simd.end(), [](auto e) { return e == false; }) );
  }
}

#endif
