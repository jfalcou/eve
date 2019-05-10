//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SHR_HPP
#define BITWISE_SHR_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/bitwise_shr.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check bitwise_shr behavior on wide",
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

  TTS_SETUP("A correctly initialized wide and shift")
  {
    int           n = sizeof(Type) * 8 - 1;
    wide<Type, T> lhs([](int i, int c) { return c - i; }),
        ref([n](int i, int c) { return eve::bitwise_shr(Type(c - i), i % n); });
    wide<i_t, T> rhs([n](int i, int) { return i % n; });

    TTS_SECTION("supports eve::bitwise_shr") { TTS_EQUAL(ref, eve::bitwise_shr(lhs, rhs)); }
    TTS_SECTION("supports >>"      ) { TTS_EQUAL(ref, (lhs >>  rhs)); }   
  }
}

TTS_CASE_TPL("Check bitwise_shr behavior on wide + scalar",
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
        ref([rhs](int i, int c) { return eve::bitwise_shr(Type(c - i), rhs); });

    TTS_SECTION("supports eve::bitwise_shr") { TTS_EQUAL(ref, eve::bitwise_shr(lhs, rhs)); }
    TTS_SECTION("supports >>"      ) { TTS_EQUAL(ref, (lhs >>  rhs)); }   
  }
}

#endif
