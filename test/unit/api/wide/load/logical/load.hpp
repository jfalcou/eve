//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOAD_HPP
#define LOAD_HPP

#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <algorithm>
#include <list>

using eve::as_aligned;
using eve::fixed;
using eve::logical;

TTS_CASE_TPL("Check ctor from unaligned pointer for logical wide",
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

  std::array<logical<Type>, T::value> ref;

  logical<Type> k = true;
  for(auto &e : ref) e = (k = !k);

  logical<wide<Type, T>> simd(&ref[ 0 ]);

  TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
}

TTS_CASE_TPL("Check ctor from aligned pointer for logical wide",
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
  constexpr auto algt = wide<Type, T>::static_alignment;

  alignas(algt) std::array<logical<Type>, T::value> ref;

  logical<Type> k = true;
  for(auto &e : ref) e = (k = !k);

  logical<wide<Type, T>> simd(as_aligned<algt>(&ref[ 0 ]));
  TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
}

TTS_CASE_TPL("Check ctor from range for logical wide",
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

  std::list<logical<Type>> ref(T::value);

  logical<Type> k = true;
  for(auto &e : ref) e = (k = !k);

  {
    logical<wide<Type, T>> simd(ref);
    TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
  }

  {
    logical<wide<Type, T>> simd(ref.begin(), ref.end());
    TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
  }
}

#endif
