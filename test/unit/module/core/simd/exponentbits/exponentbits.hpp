//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXPONENTBITS_HPP
#define EXPONENTBITS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/exponentbits.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check exponentbits behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto) { return i; }),
      ref([](auto i, auto) { return eve::exponentbits(Type(i)); });
  TTS_EQUAL(ref, eve::exponentbits(lhs));
}

#endif
