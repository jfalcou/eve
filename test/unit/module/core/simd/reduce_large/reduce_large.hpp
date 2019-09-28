//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REDUCE_LARGE_HPP
#define REDUCE_LARGE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/reduce_large.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check reduce_large behavior on wide",
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

  wide<Type, T> lhs([](auto i, auto) { return 10*i; }),
      ref([](auto i, auto) { return eve::reduce_large(Type(10*i)); });
  TTS_EQUAL(ref, eve::reduce_large(lhs));
}

#endif
