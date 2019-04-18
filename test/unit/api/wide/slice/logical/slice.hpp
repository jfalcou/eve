//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SLICE_HPP
#define SLICE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>

using eve::fixed;

TTS_CASE_TPL("Check slicing for logical wide",
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::logical;

  logical<wide<Type, T>>                      simd    ([](int i, int c) { return i < c/2; });
  logical<wide<Type, typename T::split_type>> ref_low ([](auto i, auto) { return i%2 < 2; });
  logical<wide<Type, typename T::split_type>> ref_high([](auto i, auto) { return i%2 > 3; });

  auto [ low, high ] = simd.slice();

  TTS_EQUAL(low, ref_low);
  TTS_EQUAL(simd.slice(eve::lower_), ref_low);
  TTS_EQUAL(high, ref_high);
  TTS_EQUAL(simd.slice(eve::upper_), ref_high);
}

#endif
