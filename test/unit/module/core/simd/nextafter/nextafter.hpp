//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef NEXTAFTER_HPP
#define NEXTAFTER_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/nextafter.hpp>
#include <eve/wide.hpp>
#include <eve/detail/meta.hpp>

using eve::fixed;

TTS_CASE_TPL("Check nextafter behavior on wide",
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
    ref2([](int i, int) { return eve::nextafter(Type(i % 2 ? i + 2 : -i - 2), Type(0)); }), 
    rhs(0); 
  TTS_EQUAL(ref2, eve::nextafter(lhs, Type(0)));
  TTS_EQUAL(ref2, eve::nextafter(lhs, rhs)); 
}

#endif
