//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NGTZ_HPP
#define IS_NGTZ_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_ngtz.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_ngtz behavior on wide",
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

  wide<Type, T>          lhs([](auto i, auto) { return i % 2; });
  logical<wide<Type, T>> ref([](auto i, auto) { return eve::is_ngtz(Type(i % 2)); });

  TTS_EQUAL(ref, eve::is_ngtz(lhs));
}

TTS_CASE_TPL("Check is_ngtz behavior on logical<wide>",
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

  logical<wide<Type, T>> lhs([](auto i, auto) { return (i % 2) >= 0; });
  logical<wide<Type, T>> ref([](auto i, auto) { return eve::is_ngtz(i % 2 >= 0); });

  TTS_EQUAL(ref, eve::is_ngtz(lhs));
}

#endif
