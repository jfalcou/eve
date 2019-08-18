//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_SELECT_HPP
#define BITWISE_SELECT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/bitwise_select.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check bitwise_select behavior on homogeneous wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  wide<Type,T>  lhs([](auto i, auto c) { return c-i; })
    , rhs1([](auto i, auto  ) { return i+1; })
    , rhs2([](auto i, auto  ) { return 2*i+1; })
    , ref([](auto i, auto c) { return eve::bitwise_select(Type(c-i),Type(i+1),Type(2*i+1)); });
  
  if constexpr(std::is_integral_v<Type>)
    TTS_EQUAL(ref, eve::bitwise_select(lhs, rhs1, rhs2));
  else
    TTS_IEEE_EQUAL(ref, eve::bitwise_select(lhs, rhs1, rhs2));
  
}

TTS_CASE_TPL( "Check bitwise_select behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  
  wide<Type,T>  lhs([](auto i, auto c) { return i%3; })
    ,  rhs([](auto i, auto c) { return 2*i+1; })
    , ref1([](auto i, auto c) { return eve::bitwise_select( Type(i%3), Type(2*i+1), Type(8)); })
    , ref2([](auto i, auto c) { return eve::bitwise_select( Type(i%3), Type(8),  Type(2*i+1)); }); 
  
  if constexpr(std::is_integral_v<Type>)
  {
    TTS_EQUAL(ref1, eve::bitwise_select(lhs, rhs, Type(8)));
    TTS_EQUAL(ref2, eve::bitwise_select(lhs, Type(8), rhs));
  }
  else
  {
    TTS_IEEE_EQUAL(ref1, eve::bitwise_select(lhs, rhs, Type(8)));
    TTS_IEEE_EQUAL(ref2, eve::bitwise_select(lhs, Type(8), rhs));
  }
}

#endif
