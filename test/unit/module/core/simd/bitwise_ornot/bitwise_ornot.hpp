//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel Falcou

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_ORNOT_HPP
#define BITWISE_ORNOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/simd/bitwise_ornot.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check bitwise_ornot behavior on homogeneous wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return c-i; })
                , rhs([](int i, int  ) { return i+1; })
                , ref([](int i, int c) { return eve::bitwise_ornot(Type(c-i),Type(i+1)); });

    TTS_SECTION( "supports eve::bitwise_ornot" )
    {
      if constexpr(std::is_integral_v<Type>)
        TTS_EQUAL(ref, eve::bitwise_ornot(lhs,rhs));
      else
        TTS_IEEE_EQUAL(ref, eve::bitwise_ornot(lhs,rhs));
    }
  }
}

TTS_CASE_TPL( "Check bitwise_ornot behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return i%3; })
                , ref([](int i, int c) { return eve::bitwise_ornot( Type(i%3), Type(7) ); });

    TTS_SECTION( "supports eve::bitwise_ornot" )  { TTS_EQUAL(ref, eve::bitwise_ornot(lhs,7)); }
  }
}

#endif
