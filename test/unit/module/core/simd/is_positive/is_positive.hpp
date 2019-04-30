//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_EQZ_HPP
#define IS_EQZ_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_positive.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_positive behavior on wide",
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

  wide<Type, T>           lhs([](auto i, auto c) { return c/2 - i; });
  logical<wide<Type, T>>  ref([](auto i, auto c) { return eve::is_positive(Type(c/2 - i)); });

  TTS_EQUAL(ref, eve::is_positive(lhs));
}

TTS_CASE_TPL("Check is_positive behavior on logical<wide>",
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

  logical<wide<Type, T>> lhs([](auto i, auto c) { return (c/2 - i) >= 0; });
  logical<wide<Type, T>> ref([](auto i, auto c) { return eve::is_positive( (c/2 - i) >= 0 ); });

  TTS_EQUAL(ref, eve::is_positive(lhs));
}

#endif
