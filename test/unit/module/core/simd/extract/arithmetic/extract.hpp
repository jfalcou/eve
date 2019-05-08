//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXTRACT_HPP
#define EXTRACT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/extract.hpp>
#include <eve/wide.hpp>
#include <eve/literals.hpp>

using eve::fixed;

TTS_CASE_TPL("Check extract behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
 {
  using namespace eve::literal;
  using eve::wide;

  wide<Type, T> lhs([](int i, int) { return i + 2; });

  TTS_EQUAL(Type(2)               , eve::extract(lhs, 0));
  TTS_EQUAL(Type(T::value / 2 + 2), eve::extract(lhs, T::value / 2));
  TTS_EQUAL(Type(T::value + 1)    , eve::extract(lhs, T::value - 1));

  TTS_EQUAL(Type(2)               , eve::extract(lhs, 0_c));
  TTS_EQUAL(Type(2)               , eve::extract(lhs, std::integral_constant<int, 0>()));
  TTS_EQUAL(Type(T::value / 2 + 2), eve::extract(lhs, std::integral_constant<int, T::value / 2>()));
  TTS_EQUAL(Type(T::value + 1)    , eve::extract(lhs, std::integral_constant<int, T::value - 1>()));
}

#endif
