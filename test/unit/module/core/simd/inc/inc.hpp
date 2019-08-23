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
#include <eve/function/simd/inc.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check inc behavior on wide",
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

  wide<Type, T>  lhs([](auto i, auto) { return i%2; }), 
    tst([](auto i, auto) { return i%3; }),                     
    ref([](auto i, auto) { return eve::inc(Type(i%2)); }), 
    refc([](auto i, auto) { return eve::inc[i%3](Type(i%2)); });  
  TTS_EQUAL(ref, eve::inc(lhs));
  TTS_EQUAL(refc, eve::inc[tst](lhs));
  TTS_EQUAL(lhs , eve::inc[1 > 2](lhs));
  TTS_EQUAL(eve::inc(lhs), eve::inc[3 > 2](lhs));
}


TTS_CASE_TPL("Check saturated_(inc) behavior on wide",
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
  
  wide<Type, T>  lhs([](auto i, auto) { return i%2; }), 
    tst([](auto i, auto) { return i%3; }),                     
    ref([](auto i, auto) { return eve::saturated_(eve::inc)(Type(i%2)); }), 
    refc([](auto i, auto) {return eve::saturated_(eve::inc[i%3])(Type(i%2)); });
  TTS_EQUAL(ref, eve::saturated_(eve::inc)(lhs));
  TTS_EQUAL(refc, eve::saturated_(eve::inc[tst])(lhs));
   eve::logical<wide<Type, T>> tstl([](auto i, auto) { return i%3; });
   TTS_EQUAL(refc, eve::saturated_(eve::inc[tstl])(lhs));
  
  TTS_EQUAL(lhs , eve::saturated_(eve::inc[1 > 2])(lhs));
  TTS_EQUAL(eve::saturated_(eve::inc)(lhs), eve::saturated_(eve::inc[3 > 2])(lhs));
}
#endif
