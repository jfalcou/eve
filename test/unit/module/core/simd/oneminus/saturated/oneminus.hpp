//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ONEMINUS_HPP
#define ONEMINUS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/oneminus.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check oneminus behavior on wide",
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

  wide<Type, T>  lhs([](auto i, auto) { return i%2+1; }), 
    tst([](auto i, auto) { return i%3; }),                     
    ref([](auto i, auto) { return eve::saturated_(eve::oneminus)(Type(i%2+1)); }), 
    refc([](auto i, auto) { return eve::saturated_(eve::oneminus[i%3])(Type(i%2+1)); });
  TTS_EQUAL(ref, eve::saturated_(eve::oneminus)(lhs));
  TTS_EQUAL(refc, eve::saturated_(eve::oneminus[tst])(lhs));
  TTS_EQUAL(lhs , eve::saturated_(eve::oneminus[1 > 2])(lhs));
  TTS_EQUAL(eve::saturated_(eve::oneminus)(lhs), eve::saturated_(eve::oneminus[3 > 2])(lhs));
}


#endif
