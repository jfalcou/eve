//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef AVERAGE_HPP
#define AVERAGE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/average.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/max.hpp>
#include <eve/function/min.hpp>    
#include <eve/function/sub.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check average behavior on homogeneous wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  wide<Type, T> lhs([](auto i, auto c) { return c - i; }), rhs([](auto i, auto) { return i; }),
    ref([](auto i, auto c) { return eve::average(Type(c - i), Type(i)); });
  lhs[0] = rhs[0] = ref[0] = eve::Valmax<Type>();
  
   wide<Type, T> val(eve::average(lhs, rhs)) ;
  auto z =  eve::max(ref, val) -eve::min(ref, val); 
  TTS_EQUAL(eve::is_less_equal(z, eve::One(as(ref))), eve::True(as(ref))); 
}

TTS_CASE_TPL("Check average behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> lhs([](auto i, auto c) { return Type(i % 3); }),
    ref([](auto i, auto c) { return eve::average(Type(i % 3), Type(7)); }), 
    val(eve::average(lhs, Type(7)));
  auto z =  eve::max(ref, val) -eve::min(ref, val); 

TTS_EQUAL(eve::is_less_equal(z, eve::One(as(ref))), eve::True(as(ref)));
}

#endif
