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
#include <eve/function/simd/logical_and.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check logical_and behavior on homogeneous logical<wide>",
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

  logical<wide<Type, T>> lhs([](auto i, auto c) { return i % 2 == 0; }),
      rhs([](auto i, auto c) { return i % 3 == 0; });
  logical<wide<Type, T>> ref(
      [](auto i, auto c) { return eve::logical_and(i % 2 == 0, i % 3 == 0); });

  TTS_EQUAL(ref, eve::logical_and(lhs, rhs));
  TTS_EQUAL(ref, (lhs && rhs));
}
TTS_CASE_TPL("Check logical_and behavior on homogeneous logical<wide>",
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

  logical<wide<Type, T>> lhs([](auto i, auto c) { return i % 2 == 0; }),
      rhs([](auto i, auto c) { return i % 3 == 0; });
  logical<wide<Type, T>> ref(
      [](auto i, auto c) { return eve::logical_and(i % 2 == 0, i % 3 == 0); });

  TTS_EQUAL(ref, eve::logical_and(lhs, rhs));
  TTS_EQUAL(ref, (lhs && rhs));
}

TTS_CASE_TPL("Check logical_and behavior on logical<wide> and wides",
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

  logical<wide<Type, T>> lhs([](auto i, auto c) { return i % 2 == 0; });
  wide<Type, T>          rhs([](auto i, auto c) { return i % 3; });
  logical<wide<Type, T>> ref([](auto i, auto c) { return eve::logical_and(i % 2 == 0, i % 3); });

  TTS_EQUAL(ref, eve::logical_and(lhs, rhs));
  TTS_EQUAL(ref, eve::logical_and(rhs, lhs));
  TTS_EQUAL(ref, (lhs && rhs));
  TTS_EQUAL(ref, (rhs && lhs));
}

#endif
