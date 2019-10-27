//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef UNARY_MINUS_HPP
#define UNARY_MINUS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/all.hpp>
#include <eve/function/unary_minus.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check unary_minus behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using t_t =  wide<Type, T>; 
  t_t lhs([](int i, int) { return i + 1; }),
      ref([](int i, int) { return eve::unary_minus(Type(i + 1)); });

  TTS_EQUAL(ref, eve::unary_minus(lhs));
  TTS_EQUAL(ref, -lhs);
  if constexpr(std::is_floating_point_v<T>)
  {
    TTS_EXPECT(eve::all(eve::is_negative(eve::unary_minus(t_t(0)))));
    TTS_EXPECT(eve::all(eve::is_negative(-t_t(0))));
  }
}

TTS_CASE_TPL("Check conditionnal unary_minus behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  wide<Type, T> lhs([](int i, int) { return Type(i + 1); }),
    cond([](int i, int) { return i%2 ? 1 : 0; }),
    ref([](int i, int) { return eve::unary_minus[i%2](Type(i + 1)); });
  
  TTS_EQUAL(ref, eve::unary_minus[cond](lhs));
}

#endif
