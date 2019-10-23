//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CEIL_HPP
#define CEIL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/ceil.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check ceil behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](int i, int) { return Type(i % 2 ? (i + 2) : -i - 2) / 3; }),
    ref([](int i, int) { return eve::ceil(Type(i % 2 ? i + 2 : -i - 2) / 3); });
  
  TTS_EQUAL(ref, eve::ceil(lhs));
}

#endif
