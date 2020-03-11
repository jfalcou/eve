//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOAD_HPP
#define LOAD_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/load.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;
using eve::logical;

TTS_CASE_TPL("load behavior for wide of logical",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using wide_t = eve::logical<eve::wide<EVE_TYPE, T>>;
  auto filler  = [](auto i, auto) { return i % 3 ? true : false; };

  alignas(wide_t::static_alignment) std::array<eve::logical<EVE_TYPE>, T::value> data;
  for(std::size_t i = 0; i < T::value; ++i) data[ i ] = filler(i, 0);

  wide_t simd, ref(filler);

  TTS_SUBCASE("a pointer to logical wide")
  {
    simd = eve::load(&ref);
    TTS_EQUAL(simd, ref);
  }

  TTS_SUBCASE("an aligned pointer to logical wide")
  {
    simd = eve::load(eve::as_aligned<wide_t::static_alignment>(&ref));
    TTS_EQUAL(simd, ref);
  }

  TTS_SUBCASE("a pointer to scalar logical values")
  {
    simd = eve::load(&data[ 0 ], eve::as(simd));
    TTS_EQUAL(simd, ref);
  }

  TTS_SUBCASE("an aligned pointer to scalar logical values")
  {
    simd = eve::load(eve::as_aligned<wide_t::static_alignment>(&data[ 0 ]), eve::as(simd));
    TTS_EQUAL(simd, ref);
  }
}

#endif
