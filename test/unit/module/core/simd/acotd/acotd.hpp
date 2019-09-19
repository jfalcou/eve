//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ACOTD_HPP
#define ACOTD_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/acotd.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check acotd behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::logical;

  wide<Type, T> lhs([](auto i, auto) { return i; }),
                ref([](auto i, auto) { return eve::acotd(Type(i)); });

  TTS_ULP_EQUAL(ref, eve::acotd(lhs), 1);
}

#endif
