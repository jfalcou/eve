//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_GREATER_EQUAL_HPP
#define IS_NOT_GREATER_EQUAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_greater_equal.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_not_greater_equal behavior on homogeneous logical<wide>",
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

  logical<wide<Type, T>>  lhs([](auto i, auto)  { return i%2 == 0; }),
                          rhs([](auto i, auto)  { return i%3 == 0; });

  logical<wide<Type, T>>  ref([](auto i, auto)  { return logical<Type>( (i%2 == 0) <  (i%3 == 0) ); });

  TTS_EQUAL(ref, eve::is_not_greater_equal(lhs, rhs));
}

TTS_CASE_TPL("Check is_not_greater_equal behavior on logical<wide> and scalar",
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

  logical<wide<Type, T>>  lhs([](auto i, auto)  { return i%2 == 0; });
  logical<wide<Type, T>>  refl([](auto i, auto)  { return logical<Type>( (i%2 == 0) <  true ); });
  logical<wide<Type, T>>  refr([](auto i, auto)  { return logical<Type>( true <  (i%2 == 0) ); });

  TTS_EQUAL(refl, eve::is_not_greater_equal(lhs, logical<Type>(true)));
  TTS_EQUAL(refr, eve::is_not_greater_equal(logical<Type>(true), lhs));
  TTS_EQUAL(refl, eve::is_not_greater_equal(lhs, true));
  TTS_EQUAL(refr, eve::is_not_greater_equal(true, lhs));
}

#endif
