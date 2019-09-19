//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef INPI_HPP
#define INPI_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/inpi.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check inpi behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::logical;

  wide<Type, T>  lhs([](auto i, auto) { return i; }), 
    ref([](auto i, auto) { return eve::inpi(Type(i)); });  
  TTS_ULP_EQUAL(ref, eve::inpi(lhs), 0.5);
}


#endif
