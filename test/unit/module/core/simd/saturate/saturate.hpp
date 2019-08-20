//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SATURATE_HPP
#define SATURATE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/saturate.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check saturate behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
   wide<Type, T> lhs([](int i, int) { return i + 1; }),
     ref([](int i, int) { return eve::saturate[eve::as(std::uint16_t())](Type(i + 1)); });
  
   TTS_EQUAL(ref, eve::saturate[eve::as(std::uint16_t())](lhs)); 
}


#endif
