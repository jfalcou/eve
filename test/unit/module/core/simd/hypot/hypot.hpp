//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef HYPOT_HPP
#define HYPOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/hypot.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check hypot behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  wide<Type, T> lhs([](auto i, auto c) { return Type(c - i); }),
      rhs([](auto i, auto) { return Type(i); }),
      ref([](auto i, auto c) { return eve::hypot(Type(c - i), Type(i)); });
  wide<Type, T> val(eve::hypot(lhs, rhs));
  TTS_ULP_EQUAL(ref, val, 1);
}

TTS_CASE_TPL("Check hypot behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto c) { return Type(i % 3); }),
      ref([](auto i, auto c) { return eve::hypot(Type(i % 3), Type(7)); }),
      val(eve::hypot(lhs, Type(7)));
  TTS_ULP_EQUAL(ref, val, 1);
}

#endif
