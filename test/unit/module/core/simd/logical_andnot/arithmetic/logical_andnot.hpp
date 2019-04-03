//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_ANDNOT_HPP
#define LOGICAL_ANDNOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/logical_andnot.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check logical_andnot behavior on homogeneous wide",
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

  wide<Type, T>           lhs([](auto i, auto c)  { return c - i; }),
                          rhs([](auto i, auto)    { return i % 2; });
  logical<wide<Type, T>>  ref([](auto i, auto c)  { return eve::logical_andnot(Type(c - i), Type(i % 2)); });

  TTS_EQUAL(ref, eve::logical_andnot(lhs, rhs));
}

TTS_CASE_TPL("Check plus behavior on wide and scalar",
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
  logical<wide<Type, T>> ref1([](auto i, auto) { return eve::logical_andnot(Type(i), Type(2)); });
  logical<wide<Type, T>> ref2([](auto i, auto) { return eve::logical_andnot(Type(2), Type(i)); });
  logical<wide<Type, T>> ref3([](auto i, auto) { return eve::logical_andnot(Type(i), Type(0)); });
  logical<wide<Type, T>> ref4([](auto i, auto) { return eve::logical_andnot(Type(0), Type(i)); });

  TTS_EQUAL(ref1, eve::logical_andnot(lhs, Type(2)));
  TTS_EQUAL(ref2, eve::logical_andnot(Type(2), lhs));
  TTS_EQUAL(ref3, eve::logical_andnot(lhs, Type(0)));
  TTS_EQUAL(ref4, eve::logical_andnot(Type(0), lhs));
}

#endif
