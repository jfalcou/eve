//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ZERO_ELSE_HPP
#define IF_ZERO_ELSE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/zero.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;


TTS_CASE_TPL( "Check if_zero_else"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    auto c =  eve::zero_; 
    wide<Type,T>  lhs([](int i, int c) { return i%2 ? 0 : 1; }); 
    wide<Type,T>  rhs1([](int i, int  ) { return (i%2)*i; })
      , ref([c](int i, int ) { return eve::if_else(Type(i%2 ? 0 : 1),c, Type((i%2)*i)); })
      , refs([c](int i, int ) { return eve::if_else(Type(i%2 ? 0 : 1),c, Type(2)); }); 

    TTS_SECTION( "supports eve::if_else on zero+wide" )
    {
      if constexpr(std::is_integral_v<Type>)
      {
        TTS_EQUAL(ref, eve::if_else(lhs, c, rhs1));
        TTS_EQUAL(refs, eve::if_else(lhs, c, Type(2)));
        TTS_EQUAL(ref, eve::if_else(eve::is_nez(lhs), c, rhs1));
        TTS_EQUAL(refs, eve::if_else(eve::is_nez(lhs), c, Type(2)));
      }
      else
      {
        TTS_IEEE_EQUAL(ref, eve::if_else(lhs, c, rhs1));
        TTS_IEEE_EQUAL(refs, eve::if_else(lhs, c, Type(2)));
        TTS_IEEE_EQUAL(ref, eve::if_else(eve::is_nez(lhs), c, rhs1));
        TTS_IEEE_EQUAL(refs, eve::if_else(eve::is_nez(lhs), c, Type(2)));
      }
    }
  } 
}
#endif
