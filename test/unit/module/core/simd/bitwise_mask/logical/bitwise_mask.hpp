//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_MASK_HPP
#define BITWISE_MASK_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/simd/bitwise_mask.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>

using eve::fixed;

TTS_CASE_TPL("Check bitwise_mask behavior on logical wide",
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

  logical<wide<Type, T>> lhs([](int i, int) { return i % 2 == 0; });
  wide<Type, T> ref([](int i, int) { return eve::bitwise_mask(logical<Type>(i % 2 == 0)); });

  if constexpr(std::is_integral_v<Type>)
    TTS_EQUAL(ref, eve::bitwise_mask(lhs));
  else
    TTS_IEEE_EQUAL(ref, eve::bitwise_mask(lhs));
}

#endif
