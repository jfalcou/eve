//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CONJ_HPP
#define CONJ_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/conj.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check conj behavior on wide",
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

  wide<Type, T> lhs([](auto i, auto) { return i; }),
      ref([](auto i, auto) { return eve::conj(Type(i)); });
  TTS_EQUAL(ref, eve::conj(lhs));
}

#endif
