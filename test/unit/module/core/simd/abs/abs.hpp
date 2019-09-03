//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ABS_HPP
#define ABS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/abs.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check abs behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](int i, int) { return i % 2 ? i + 2 : -i - 2; }),
      ref([](int i, int) { return eve::abs(Type(i % 2 ? i + 2 : -i - 2)); });

  TTS_EQUAL(ref, eve::abs(lhs));
}

#endif
