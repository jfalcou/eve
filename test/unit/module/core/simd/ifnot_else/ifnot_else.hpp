//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IFNOT_ELSE_HPP
#define IFNOT_ELSE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/ifnot_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL( "Check ifnot_else behavior on homogeneous wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return c-i; })
                , rhs1([](int i, int  ) { return i+1; })
                , rhs2([](int i, int  ) { return 2*i+1; })
                , ref([](int i, int c) { return eve::ifnot_else(Type(c-i),Type(i+1),Type(2*i+1)); });

    TTS_SECTION( "supports eve::ifnot_else" )
    {
      if constexpr(std::is_integral_v<Type>)
      {
        TTS_EQUAL(ref, eve::ifnot_else(lhs, rhs1, rhs2));
        TTS_EQUAL(ref, eve::ifnot_else(eve::is_nez(lhs), rhs1, rhs2));
      }
      else
      {
        TTS_IEEE_EQUAL(ref, eve::ifnot_else(lhs, rhs1, rhs2));
        TTS_IEEE_EQUAL(ref, eve::ifnot_else(eve::is_nez(lhs), rhs1, rhs2));
      }
    }
  }
}

TTS_CASE_TPL( "Check ifnot_else behavior on wide + scalar"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64> 
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return i%3; })
      , ref([](int i, int c) { return eve::ifnot_else( Type(i%3), Type(7), Type(8)); });

    TTS_SECTION( "supports eve::ifnot_else" )
    {
      if constexpr(std::is_integral_v<Type>)
        TTS_EQUAL(ref, eve::ifnot_else(lhs, Type(7), Type(8)));
      else
        TTS_IEEE_EQUAL(ref, eve::ifnot_else(lhs, Type(7), Type(8)));
    }
  }
}

TTS_CASE_TPL( "Check ifnot_else behavior on homogeneous logical wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;
 
  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return i%2 ? 0 : 1; }); 
    wide<eve::logical<Type>,T>  rhs1([](int i, int  ) { return i%2 == 0; })
      , rhs2([](int i, int  ) { return i%3 == 0; })
      , ref([](int i, int c) { return eve::ifnot_else(Type(i%2 ? 0 : 1),i%2 == 0,i%3 == 0); })
      , lhs1([](int i, int c) { return !(i%2 == 0); }); 

    TTS_SECTION( "supports eve::ifnot_else on wide logical" )
    {
        TTS_EQUAL(ref, eve::ifnot_else(lhs, rhs1, rhs2));
    }
  }
}

TTS_CASE_TPL( "Check ifnot_else behavior on homogeneous logical wide"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    wide<Type,T>  lhs([](int i, int c) { return i%2 ? 0 : 1; }); 
    wide<eve::logical<Type>,T>  rhs1([](int i, int  ) { return i%2 == 0; })
      , ref([](int i, int c) { return eve::ifnot_else(Type(i%2 ? 0 : 1),i%2 == 0,true); }); 
    eve::logical<Type>  rhs2(true); 
    std::cout << "lhs  " << lhs << std::endl;
    std::cout << "rhs1 " << rhs1<< std::endl;
    std::cout << "rhs2 " << rhs2<< std::endl;
    std::cout << "ref  " << ref << std::endl;  
    TTS_SECTION( "supports eve::ifnot_else on wide logical/logical" )
    {
        TTS_EQUAL(ref, eve::ifnot_else(lhs, rhs1, rhs2));
    }
  } 
}

#endif
