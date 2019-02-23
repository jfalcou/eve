//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SELECT_HPP
#define BITWISE_SELECT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/bitwise_select.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check bitwise_select behavior on homogeneous wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return c-i; })
                , rhs1([](int i, int  ) { return i+1; })
                , rhs2([](int i, int  ) { return 2*i+1; })
                , ref([](int i, int c) { return eve::bitwise_select(Type(c-i),Type(i+1),Type(2*i+1)); });

    TTS_SECTION( "supports eve::bitwise_select" )
    {
      if constexpr(std::is_integral_v<Type>)
        TTS_EQUAL(ref, eve::bitwise_select(lhs, rhs1, rhs2));
      else
        TTS_IEEE_EQUAL(ref, eve::bitwise_select(lhs, rhs1, rhs2));
    }
  }
}

TTS_CASE_TPL( "Check bitwise_select behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return i%3; })
      , ref([](int i, int c) { return eve::bitwise_select( Type(i%3), Type(7), Type(8)); });

    TTS_SECTION( "supports eve::bitwise_select" )
    {
      if constexpr(std::is_integral_v<Type>)
        TTS_EQUAL(ref, eve::bitwise_select(lhs, Type(7), Type(8)));
      else
        TTS_IEEE_EQUAL(ref, eve::bitwise_select(lhs, Type(7), Type(8)));
    }
  }
}

#endif
