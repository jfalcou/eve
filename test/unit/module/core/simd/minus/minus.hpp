//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MINUS_HPP
#define MINUS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/minus.hpp>
#include <eve/pack.hpp>

using eve::fixed;

TTS_CASE_TPL( "Check minus behavior on pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;

  TTS_SETUP( "A correctly initialized pack" )
  {
    pack<Type,T>  lhs([](int i, int c) { return c+i; })
                , rhs([](int i, int  ) { return i;   })
                , ref(T::value);

    TTS_SECTION( "supports eve::minus" )
    {
      TTS_EQUAL(ref, eve::minus(lhs,rhs));
    }

    TTS_SECTION( "supports operator-()" )
    {
      TTS_EQUAL(ref, lhs - rhs);
    }
  }
}

#endif
