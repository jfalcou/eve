//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REM_PIO2_MEDIUM_HPP
#define REM_PIO2_MEDIUM_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/rem_pio2_medium.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check rem_pio2_medium behavior on wide",
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

  wide<EVE_TYPE, T> lhs([](auto i, auto) { return 10*i; }),
      ref([](auto i, auto) { return eve::rem_pio2_medium(EVE_TYPE(10*i)); });
  TTS_EQUAL(ref, eve::rem_pio2_medium(lhs));
}

#endif
