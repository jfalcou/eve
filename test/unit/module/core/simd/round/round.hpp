//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_ROUND_HPP
#define IS_ROUND_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/round.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/scalar/round.hpp>
#include <eve/function/scalar/ceil.hpp>
#include <eve/function/scalar/trunc.hpp>
#include <eve/function/scalar/floor.hpp>
#include <eve/function/scalar/nearest.hpp>
using eve::fixed;

TTS_CASE_TPL("Check round behavior on wide",
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

  wide<Type, T>  lhs([](auto i, auto) { return Type(i)/3; }), 
    ref([](auto i, auto) { return eve::round(Type(i)/3); }), 
    ref1([](auto i, auto) { return eve::round[eve::up_](Type(i)/3); }), 
    ref2([](auto i, auto) { return eve::round[eve::to_zero_](Type(i)/3); }), 
    ref3([](auto i, auto) { return eve::round[eve::down_](Type(i)/3); }), 
    ref4([](auto i, auto) { return eve::round[eve::nearest_int_](Type(i)/3); }); 
    
    TTS_EQUAL(ref, eve::round(lhs));
  TTS_EQUAL(ref1, eve::round[eve::up_](lhs));
  TTS_EQUAL(ref2, eve::round[eve::to_zero_](lhs));
  TTS_EQUAL(ref3, eve::round[eve::down_](lhs));
  TTS_EQUAL(ref4, eve::round[eve::nearest_int_](lhs));

}


#endif
