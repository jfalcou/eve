//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOAD_HPP
#define LOAD_HPP

#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/wide.hpp>
#include <algorithm>
#include <list>

using eve::as_aligned;
using eve::fixed;

TTS_CASE_TPL("Check ctor from unaligned pointer for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  std::array<EVE_TYPE, T::value> ref;

  EVE_TYPE k = {};
  for(auto &e : ref) e = k++;

  wide<EVE_TYPE, T> simd(&ref[ 0 ]);

  TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
}

TTS_CASE_TPL("Check ctor from aligned pointer for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  constexpr auto algt = wide<EVE_TYPE, T>::static_alignment;

  alignas(algt) std::array<EVE_TYPE, T::value> ref;

  EVE_TYPE k = {};
  for(auto &e : ref) e = k++;

  wide<EVE_TYPE, T> simd(as_aligned<algt>(&ref[ 0 ]));
  TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
}

TTS_CASE_TPL("Check ctor from range for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  std::list<EVE_TYPE> ref(T::value);

  EVE_TYPE k = {};
  for(auto &e : ref) e = k++;

  {
    wide<EVE_TYPE, T> simd(ref);
    TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
  }

  {
    wide<EVE_TYPE, T> simd(ref.begin(), ref.end());
    TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
  }
}

#endif
