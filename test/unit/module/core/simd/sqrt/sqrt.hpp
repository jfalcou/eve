//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SQRT_HPP
#define SQRT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/sqrt.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check sqrt behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto) { return i; }),
      ref([](auto i, auto) { return eve::sqrt(Type(i)); });
  TTS_ULP_EQUAL(ref, eve::sqrt(lhs), 1);
}

TTS_CASE_TPL("Check raw_(sqrt) behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto) { return 1 + i; }),
      ref([](auto i, auto) { return eve::sqrt(Type(1 + i)); });
  TTS_RELATIVE_EQUAL(ref, eve::raw_(eve::sqrt)(lhs), 1);
}

#endif
