//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
             fixed<64>
            )
{
  using eve::wide;
  using eve::logical;

  wide<EVE_TYPE, T>  lhs([](auto i, auto) { return (i%2 ? 1:-1)*40*eve::Pio_4<EVE_TYPE>()/EVE_TYPE(i+1); }), 
    ref([](auto i, auto) { return eve::big_(eve::cosd)( (i%2 ? 1:-1)*40*eve::Pio_4<EVE_TYPE>()/EVE_TYPE(i+1)); });
  TTS_ULP_EQUAL(ref, eve::big_(eve::cosd)(lhs), 0.5);
}


#endif
