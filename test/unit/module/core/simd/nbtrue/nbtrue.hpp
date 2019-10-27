//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NBTRUE_HPP
#define NBTRUE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/nbtrue.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/is_nez.hpp>

using eve::fixed;

TTS_CASE_TPL("Check nbtrue behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::wide;

  wide<Type, T> lhs([](int i, int) { return Type(1); });
  uint32_t v = T::value; 
  TTS_EQUAL(v, eve::nbtrue(lhs));

  for( uint32_t j=0; j < v; ++j)
  {
    wide<Type, T> rhs1([j](uint32_t i, uint32_t) { return i >= j ? 0 : 1; });
    wide<Type, T> rhs2([j](uint32_t i, uint32_t) { return i <= j ? 0 : 1; });
    wide<Type, T> rhs3([j](uint32_t i, uint32_t) { return i == j ? 1 : 0; });
    wide<Type, T> rhs4([j](uint32_t i, uint32_t) { return 0; });

    TTS_EQUAL(j, eve::nbtrue(rhs1));
    TTS_EQUAL( v-1u-j, eve::nbtrue(rhs2));
    TTS_EQUAL((1u), eve::nbtrue(rhs3));

    TTS_EQUAL(0u, eve::nbtrue(rhs4));
  }
}

#endif
