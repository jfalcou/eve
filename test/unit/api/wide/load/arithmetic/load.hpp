//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include "test.hpp"

#include <tts/tests/basic.hpp>
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/wide.hpp>
#include <algorithm>
#include <vector>
#include <list>

using eve::as_aligned;
using eve::fixed;

template<typename T, typename N>
auto data_block()
{
  using alloc_t = eve::aligned_allocator<T, eve::wide<T, N>::static_alignment>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - N::value;
  std::vector<T, alloc_t> ref(nb_elem);

  T k = {};
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = k++;

  return std::pair{ref,start};
}

TTS_CASE_TPL("Check ctor from unaligned pointer for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  auto [data,idx] = data_block<EVE_TYPE, T>();
  auto* ref = &data[idx];

  eve::wide<EVE_TYPE, T> simd(ref);
  TTS_EXPECT( std::equal(simd.begin(), simd.end(), ref) );
}

TTS_CASE_TPL("Check ctor from const unaligned pointer for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  auto [data,idx] = data_block<EVE_TYPE, T>();
  auto const* ref = &data[idx];

  eve::wide<EVE_TYPE, T> simd(ref);
  TTS_EXPECT( std::equal(simd.begin(), simd.end(), ref) );
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
  auto constexpr algt = eve::wide<EVE_TYPE, T>::static_alignment;
  auto [data,idx] = data_block<EVE_TYPE, T>();
  auto*       ref = &data[idx];

  eve::wide<EVE_TYPE, T> simd(as_aligned<algt>(ref));
  TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref));
}

TTS_CASE_TPL("Check ctor from const aligned pointer for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  auto constexpr algt = eve::wide<EVE_TYPE, T>::static_alignment;
  auto [data,idx] = data_block<EVE_TYPE, T>();
  auto const* ref = &data[idx];

  eve::wide<EVE_TYPE, T> simd(as_aligned<algt>(ref));
  TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref));
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
