//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#ifndef SPLAT_HPP
#define SPLAT_HPP

#include <eve/pack.hpp>
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

#endif
