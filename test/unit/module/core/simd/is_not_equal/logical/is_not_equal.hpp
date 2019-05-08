//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_EQUAL_HPP
#define IS_NOT_EQUAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_equal.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_not_equal behavior on homogeneous wide<logical>",
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

  logical<wide<Type, T>>  lhs([](auto i, auto c) { return i%2 == 0; })
                        , rhs([](auto i, auto c) { return i%3 == 0; });
  logical<wide<Type, T>>  ref([](auto i, auto c) { return eve::is_not_equal(i%2 == 0, i%3 == 0); });
  TTS_EQUAL(ref, eve::is_not_equal(lhs, rhs));
  TTS_EQUAL(ref, (lhs !=  rhs));
}

TTS_CASE_TPL("Check is_not_equal behavior on logical<wide> + scalar",
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

  logical<wide<Type, T>>  lhs([](auto i, auto c) { return i%2 == 0; });
  logical<wide<Type, T>>  ref([](auto i, auto c) { return eve::is_not_equal(i%2 == 0, true); });

  TTS_EQUAL(ref, eve::is_not_equal(lhs , true));
  TTS_EQUAL(ref, eve::is_not_equal(true, lhs));
  TTS_EQUAL(ref, eve::is_not_equal(lhs, logical<Type>(true)));
  TTS_EQUAL(ref, eve::is_not_equal(logical<Type>(true), lhs));
  TTS_EQUAL(ref, (lhs !=  true));
  TTS_EQUAL(ref, (true != lhs));
  TTS_EQUAL(ref, (lhs !=  logical<Type>(true)));
  TTS_EQUAL(ref, (logical<Type>(true) != lhs));
}

#endif
