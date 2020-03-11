//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COSD_HPP
#define COSD_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/cosd.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check cosd behavior on wide",
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

  wide<EVE_TYPE, T>  lhs([c](auto i, auto) { return Pio_4<EVE_TYPE>()/EVE_TYPE(i); }), 
    ref([](auto i, auto) { return eve::restricted_(eve::cosd)(Pio_4<EVE_TYPE>()/(EVE_TYPE(i)); });  
  TTS_ULP_EQUAL(ref, eve::restricted_(eve::cosd)(lhs), 0.5);
}


#endif
