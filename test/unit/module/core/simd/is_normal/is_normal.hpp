//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NORMAL_HPP
#define IS_NORMAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_normal.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_normal behavior on wide",
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

  if constexpr(std::is_integral_v<Type>)
  {
    wide<Type, T> lhs([](auto i, auto) { return i/2; });
    logical<wide<Type, T>> ref([](auto i, auto) { return eve::is_normal(i/2); });
    TTS_EQUAL(eve::is_normal(lhs),  ref );
  }
  else
  {
    Type s = eve::Smallestposval<Type>();
    wide<Type, T> lhs([&](auto i, auto c) { return i%2 ? s*i : s/i; });
    lhs.back() = 0;

    logical<wide<Type, T>> ref([&](auto i, auto c) { return eve::is_normal(lhs[i]); });
    TTS_EQUAL(eve::is_normal(lhs), ref);
  }
}

TTS_CASE_TPL("Check is_normal behavior on logical<wide>",
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

  logical<wide<Type, T>> lhs([](auto i, auto) { return i%2 == 1; });
  logical<wide<Type, T>> ref([](auto i, auto) { return eve::is_normal( i%2 == 1); });
  TTS_EQUAL(eve::is_normal(lhs), ref);
}

#endif
