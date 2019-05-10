//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_LESSGREATER_HPP
#define IS_LESSGREATER_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_lessgreater.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_lessgreater behavior on homogeneous logical<wide>",
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

  logical<wide<Type, T>>  ref([](auto i, auto)  { return eve::is_lessgreater( (i%2 == 0), (i%3 == 0) ); });
  TTS_EQUAL(ref, eve::is_lessgreater(lhs, rhs));

}

TTS_CASE_TPL("Check is_lessgreater behavior on logical<wide> and scalar",
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
  logical<wide<Type, T>>  refl([](auto i, auto)  { return eve::is_lessgreater( (i%2 == 0),  true ); });
  logical<wide<Type, T>>  refr([](auto i, auto)  { return eve::is_lessgreater( true, (i%2 == 0) ); });

  TTS_EQUAL(refl, eve::is_lessgreater(lhs, logical<Type>(true)));
  TTS_EQUAL(refr, eve::is_lessgreater(logical<Type>(true), lhs));
  TTS_EQUAL(refl, eve::is_lessgreater(lhs, true));
  TTS_EQUAL(refr, eve::is_lessgreater(true, lhs));
}

#endif
