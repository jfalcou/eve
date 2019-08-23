//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_ORNOT_HPP
#define LOGICAL_ORNOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/logical_ornot.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check logical_ornot behavior on homogeneous logical<wide>",
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

  logical<wide<Type, T>>  lhs([](auto i, auto c) { return i%2 ==  0; }),
                          rhs([](auto i, auto c) { return i%3 ==  0; });
  logical<wide<Type, T>>  ref([](auto i, auto c) { return eve::logical_ornot(i%2 == 0, i%3 == 0); });

  TTS_EQUAL(ref, eve::logical_ornot(lhs, rhs));
}


TTS_CASE_TPL("Check logical_ornot behavior on logical<wide> and scalars",
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

  logical<wide<Type, T>>  lhs([](auto i, auto c) { return i%2 ==  0; });
  logical<wide<Type, T>> ref1([](auto i, auto c) { return eve::logical_ornot(i%2 == 0, true); });
  logical<wide<Type, T>> ref2([](auto i, auto c) { return eve::logical_ornot(true, i%2 == 0); });
  logical<wide<Type, T>> ref3([](auto i, auto c) { return eve::logical_ornot(i%2 == 0, false); });
  logical<wide<Type, T>> ref4([](auto i, auto c) { return eve::logical_ornot(false, i%2 == 0); });

  TTS_EQUAL(ref1, eve::logical_ornot(lhs   , true  ) );
  TTS_EQUAL(ref1, eve::logical_ornot(lhs   , 3     ) );
  TTS_EQUAL(ref2, eve::logical_ornot(true  , lhs   ) );
  TTS_EQUAL(ref2, eve::logical_ornot(3     , lhs   ) );
  TTS_EQUAL(ref3, eve::logical_ornot(lhs   , false ) );
  TTS_EQUAL(ref3, eve::logical_ornot(lhs   , 0     ) );
  TTS_EQUAL(ref4, eve::logical_ornot(false , lhs   ) );
  TTS_EQUAL(ref4, eve::logical_ornot(0     , lhs   ) );
}

TTS_CASE_TPL("Check logical_ornot behavior on logical<wide> and wides",
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

  logical<wide<Type, T>>  lhs([](auto i, auto c) { return i%2 ==  0; });
  wide<Type, T>  rhs([](auto i, auto c) { return i%3; });
  logical<wide<Type, T>> ref([](auto i, auto c) { return eve::logical_ornot(i%2 == 0, i%3 ); }); 
  logical<wide<Type, T>> ref1([](auto i, auto c) { return eve::logical_ornot( i%3, i%2 == 0); });

  TTS_EQUAL(ref, eve::logical_ornot(lhs, rhs));
  TTS_EQUAL(ref1, eve::logical_ornot(rhs, lhs));
}
#endif
