//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_AND_HPP
#define LOGICAL_AND_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/logical_or.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check logical_or behavior on homogeneous logical<wide>",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::wide;
  using eve::logical;

  logical<wide<Type, T>>  lhs([](auto i, auto c) { return i%2 ==  0; }),
                          rhs([](auto i, auto c) { return i%3 ==  0; });
  logical<wide<Type, T>>  ref([](auto i, auto c) { return eve::logical_or(i%2 == 0, i%3 == 0); });

  TTS_EQUAL(ref, eve::logical_or(lhs, rhs));
  TTS_EQUAL(ref, (lhs ||  rhs));
}


TTS_CASE_TPL("Check logical_or behavior on logical<wide> or scalars",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::wide;
  using eve::logical;

  logical<wide<Type, T>>  lhs([](auto i, auto c) { return i%2 ==  0; });
  logical<Type>           rhs = true;
  Type                    srhs = 3;
  logical<wide<Type, T>> ref([](auto i, auto c) { return eve::logical_or(i%2 == 0, true); });

  TTS_EQUAL(ref, eve::logical_or(lhs, rhs));
  TTS_EQUAL(ref, eve::logical_or(lhs, srhs));
  TTS_EQUAL(ref, eve::logical_or(rhs, lhs));
  TTS_EQUAL(ref, eve::logical_or(srhs, lhs));
  TTS_EQUAL(ref, (lhs || rhs));
  TTS_EQUAL(ref, (lhs || srhs));
  TTS_EQUAL(ref, (rhs || lhs));
  TTS_EQUAL(ref, (srhs || lhs));
}

#endif
