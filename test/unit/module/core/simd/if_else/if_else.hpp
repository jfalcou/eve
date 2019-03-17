//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ELSE_HPP
#define IF_ELSE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check if_else behavior on homogeneous wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  using eve::is_nez; 
  using l_t =  eve::logical<Type>; 
  wide<Type,T>  cond([](int i, int ) { return (i%2)*i; })
    , rhs1([](int i, int  ) { return i%2+1; })
    , rhs2([](int i, int  ) { return i%3; }); 

  wide<Type,T>  ref([](int i, int ) { return eve::if_else(Type((i%2)*i),Type(i%2+1),Type(i%3)); });

  wide<l_t, T> lref([](int i, int ) { return eve::if_else(Type((i%2)*i),l_t(i%2+1),l_t(i%3)); }); 

  TTS_EQUAL(ref, eve::if_else(cond, rhs1, rhs2));                          //w w w
  TTS_EQUAL(ref, eve::if_else(is_nez(cond), rhs1, rhs2));                  //lw w w
  TTS_EQUAL(lref, eve::if_else(cond, is_nez(rhs1), is_nez(rhs2)));         //w lw lw
  TTS_EQUAL(lref, eve::if_else(is_nez(cond), is_nez(rhs1), is_nez(rhs2))); //lw lw lw 
}

TTS_CASE_TPL( "Check if_else behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64> 
            )
{
  using eve::wide;
  using eve::is_nez; 
  
  wide<Type,T>  lhs([](int i, int ) { return i%3; })
    , refss([](int i, int ) { return eve::if_else( Type(i%3), Type(7), Type(8)); })
    , refsw([](int i, int ) { return eve::if_else( Type(i%3), Type(7), Type(i*(i%2))); })
    , refws([](int i, int ) { return eve::if_else( Type(i%3), Type(i*(i%2)), Type(8)); })
    ,  x([](int i, int ) { return i*(i%2); }); 
  TTS_EQUAL(refss, eve::if_else(lhs, Type(7), Type(8)));               //w s s
  TTS_EQUAL(refsw, eve::if_else(lhs, Type(7), x));                     //w s w
  TTS_EQUAL(refws, eve::if_else(lhs, x, Type(8)));                     //w w s
  TTS_EQUAL(refss, eve::if_else(is_nez(lhs), Type(7), Type(8)));       //lw s s
  TTS_EQUAL(refsw, eve::if_else(is_nez(lhs), Type(7), x));             //lw s w
  TTS_EQUAL(refws, eve::if_else(is_nez(lhs), x, Type(8)));             //lw w s

  eve::logical<Type> t = eve::True<Type>();
  eve::logical<Type> f = eve::False<Type>();
  using l_t = wide<eve::logical<Type>, T>;
  l_t  lrefss([t, f](int i, int ) { return eve::if_else( Type(i%3), t,  f); })
    , lrefsw([t](int i, int ) { return eve::if_else( Type(i%3), t,  is_nez(Type((i%2)*i))); })
    , lrefws([f](int i, int ) { return eve::if_else( Type(i%3), is_nez(Type((i%2)*i)), f); }); 
  l_t lx(is_nez(x)); 
   TTS_EQUAL(lrefss, eve::if_else(lhs, t, f));               //w ls ls
   TTS_EQUAL(lrefsw, eve::if_else(lhs, t, lx));              //w ls lw
   TTS_EQUAL(lrefws, eve::if_else(lhs, lx, f));              //w lw ls
   TTS_EQUAL(lrefss, eve::if_else(is_nez(lhs), t, f));       //lw ls ls
   TTS_EQUAL(lrefsw, eve::if_else(is_nez(lhs), t, lx));      //lw ls lw
   TTS_EQUAL(lrefws, eve::if_else(is_nez(lhs), lx, f));      //lw lw ls
}


#endif
