//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IFNOT_ELSE_HPP
#define IFNOT_ELSE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/ifnot_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check ifnot_else behavior on homogeneous wide"
            , fixed<1>,fixed<2>, fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  using eve::is_nez;
  using l_t =  eve::logical<wide<Type,T>>;

  wide<Type,T>  cond([](auto i, auto ) { return (i%2)*i; });

  l_t   lref([](auto i, auto ) { return eve::ifnot_else(Type((i%2)*i),i%2,i%3); })
      , rhs1([](auto i, auto ) { return (i%2) != 0; })
      , rhs2([](auto i, auto ) { return (i%3) != 0; });

  TTS_EQUAL(lref, eve::ifnot_else(cond        , rhs1, rhs2)); //w lw lw
  TTS_EQUAL(lref, eve::ifnot_else(is_nez(cond), rhs1, rhs2)); //lw lw lw
}

TTS_CASE_TPL( "Check ifnot_else behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
  using eve::is_nez;

  eve::logical<Type> t(true);
  eve::logical<Type> f(false);

  using l_t =  eve::logical<wide<Type,T>>;

  wide<Type,T>  cond([](auto i, auto ) { return i%3; });

  l_t   lrefss([t, f](auto i, auto ) { return eve::ifnot_else( Type(i%3), t,  f); })
      , lrefsw([t](auto i, auto ) { return eve::ifnot_else( Type(i%3), t,  is_nez(Type((i%2)*i))); })
      , lrefws([f](auto i, auto ) { return eve::ifnot_else( Type(i%3), is_nez(Type((i%2)*i)), f); });

  l_t lx([](auto i, auto ) { return ((i%2)*i) != 0; });

   TTS_EQUAL(lrefsw, eve::ifnot_else(cond, t, lx));              //w ls lw
   TTS_EQUAL(lrefws, eve::ifnot_else(cond, lx, f));              //w lw ls
   TTS_EQUAL(lrefsw, eve::ifnot_else(is_nez(cond), t, lx));      //lw ls lw
   TTS_EQUAL(lrefws, eve::ifnot_else(is_nez(cond), lx, f));      //lw lw ls
}

#endif
