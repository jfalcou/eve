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
#include <eve/function/simd/logical_xor.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check logical_xor behavior on homogeneous wide",
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

  wide<Type, T>           lhs([](auto i, auto c) { return c - i; }),
                          rhs([](auto i, auto) { return i % 2; });
  logical<wide<Type, T>>  ref([](auto i, auto c) { return eve::logical_xor(Type(c - i), Type(i % 2)); });

  TTS_EQUAL(ref, eve::logical_xor(lhs, rhs));
}

TTS_CASE_TPL("Check plus behavior on wide xor scalar",
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

  wide<Type, T>           lhs([](auto i, auto) { return i; });
  logical<wide<Type, T>> ref1([](auto i, auto) { return eve::logical_xor(Type(i), Type(2)); });
  logical<wide<Type, T>> ref2([](auto i, auto) { return eve::logical_xor(Type(i), Type(0)); });

  TTS_EQUAL(ref1, eve::logical_xor(lhs, Type(2)));
  TTS_EQUAL(ref1, eve::logical_xor(Type(2), lhs));
  TTS_EQUAL(ref2, eve::logical_xor(lhs, Type(0)));
  TTS_EQUAL(ref2, eve::logical_xor(Type(0), lhs));
}

#endif
