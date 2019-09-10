//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_DIV_HPP
#define IF_DIV_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/div.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check conditional div behavior on homogeneous wide"
            , fixed<1>,fixed<2>, fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  using eve::is_nez;

  wide<Type,T>  cond([](auto i, auto ) { return (i%2)*i; })
              , rhs1([](auto i, auto ) { return i%2+1; })
              , rhs2([](auto i, auto ) { return i%3+1; });

  wide<Type,T>  ref([](int i, int ) { return eve::div[Type((i%2)*i)](Type(i%2+1),Type(i%3+1)); });

  TTS_ULP_EQUAL(ref , eve::div[cond]( rhs1, rhs2), 0.5);          //w w w
  TTS_ULP_EQUAL(ref , eve::div[is_nez(cond)]( rhs1, rhs2), 0.5);  //lw w w
}

TTS_CASE_TPL( "Check conditional div behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  using eve::is_nez;

  wide<Type,T>  rhs1([](auto i, auto ) { return i%2+1; })
              , rhs2([](auto i, auto ) { return i%3+1; })
              , cond([](auto i, auto ) { return i%2;   });     

  wide<Type,T>  ref1([](int i, int ) { return eve::div[true](Type(i%2+1),Type(i%3+1)); }),
    ref2([](int i, int ) { return eve::div[false](Type(i%2+1),Type(i%3+1)); }),
    ref3([](int i, int ) { return eve::div[i%2  ](Type(7),Type(i%3+1)); });

  TTS_ULP_EQUAL(ref1 , eve::div[true]( rhs1, rhs2), 0.5);      
  TTS_ULP_EQUAL(ref2 , eve::div[false]( rhs1, rhs2), 0.5);  
  TTS_ULP_EQUAL(ref3 , eve::div[cond](Type(7), rhs2), 0.5); 
}

#endif
