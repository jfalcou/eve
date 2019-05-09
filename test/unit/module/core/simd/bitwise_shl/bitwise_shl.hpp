//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_bitwise_shl_HPP
#define BITWISE_bitwise_shl_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/simd/bitwise_shl.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check bitwise_shl behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using i_t = eve::detail::as_integer_t<Type>;
  
  std::ptrdiff_t n = sizeof(Type) * 8 - 1;
  wide<Type, T>  lhs([](int i, int c) { return c - i; }),
    ref([n](int i, int c) { return eve::bitwise_shl(Type(c - i), i % n); });
  wide<i_t, T> rhs([n](int i, int) { return i % n; });
  
  TTS_EQUAL(ref, eve::bitwise_shl(lhs, rhs)); 
  TTS_EQUAL(ref, lhs << rhs); 
}

TTS_CASE_TPL("Check bitwise_shl behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  
  TTS_SETUP("A correctly initialized wide and a scalar shift")
  {
    auto          rhs = sizeof(Type) * 4;
    wide<Type, T> lhs([](int i, int c) { return c - i; }),
      ref([rhs](int i, int c) { return eve::bitwise_shl(Type(c - i), rhs); });
    
    TTS_EQUAL(ref, eve::bitwise_shl(lhs, rhs)); 
    TTS_EQUAL(ref, lhs << rhs); 
  }
}

#endif
