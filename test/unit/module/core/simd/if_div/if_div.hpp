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
#include <eve/function/add.hpp>
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

  TTS_EQUAL(ref , eve::div[cond]( rhs1, rhs2));          //w w w
  TTS_EQUAL(ref , eve::div[is_nez(cond)]( rhs1, rhs2));  //lw w w
}

TTS_CASE_TPL( "Check conditional div behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  using eve::is_nez;

  wide<Type,T>    lhs([](int i, int ) { return i%3; })
    , refss([](int i, int ) { return eve::div[ Type(i%3)]( Type(7), Type(8)); })
    , refsw([](int i, int ) { return eve::div[ Type(i%3)]( Type(7), Type(i*(i%2)+1)); })
    , refws([](int i, int ) { return eve::div[ Type(i%3)]( Type(i*(i%2)+1), Type(8)); })
    ,     x([](int i, int ) { return i*(i%2)+1; });

  TTS_EQUAL(refss, eve::div[lhs        ](Type(7) , Type(8) )); //w s s
  TTS_EQUAL(refsw, eve::div[lhs        ](Type(7) , x       )); //w s w
  TTS_EQUAL(refws, eve::div[lhs        ]( x       , Type(8) )); //w w s
  TTS_EQUAL(refss, eve::div[is_nez(lhs)]( Type(7) , Type(8) )); //lw s s
  TTS_EQUAL(refsw, eve::div[is_nez(lhs)]( Type(7) , x       )); //lw s w
  TTS_EQUAL(refws, eve::div[is_nez(lhs)]( x       , Type(8) )); //lw w s
}

#endif
