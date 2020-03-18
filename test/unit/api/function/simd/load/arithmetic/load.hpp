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
#include <tts/tests/relation.hpp>
#include <eve/function/load.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("load behavior for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using wide_t = eve::wide<EVE_TYPE, T>;
  auto filler  = [](auto i, auto) { return EVE_TYPE(1) + i; };

  alignas(wide_t::static_alignment) std::array<EVE_TYPE, T::value> data;
  for(int i = 0; i < T::value; ++i) data[ i ] = filler(i, 0);

  TTS_WHEN("We initialize some value")
  {
    wide_t simd, ref(filler);

    TTS_AND_THEN("We load a pointer to wide")
    {
      simd = eve::load(&ref);
      TTS_EQUAL(simd, ref);
    }

    TTS_AND_THEN("We load an aligned pointer to wide")
    {
      simd = eve::load(eve::as_aligned<wide_t::static_alignment>(&ref));
      TTS_EQUAL(simd, ref);
    }

    TTS_AND_THEN("We load a pointer to scalar values")
    {
      simd = eve::load(&data[ 0 ], eve::as(simd));
      TTS_EQUAL(simd, ref);
    }

    TTS_AND_THEN("We load an aligned pointer to scalar values")
    {
      simd = eve::load(eve::as_aligned<wide_t::static_alignment>(&data[ 0 ]), eve::as(simd));
      TTS_EQUAL(simd, ref);
    }
  }
}

#endif
