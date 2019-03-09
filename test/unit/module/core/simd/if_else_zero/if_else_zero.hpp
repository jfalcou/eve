//==================================================================================================
/** 
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IF_ELSE_ZERO_HPP
#define IF_ELSE_ZERO_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/constant/zero.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;


TTS_CASE_TPL( "Check if_else_zero"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::wide;

  TTS_SETUP( "A correctly initialized wide" )
  {
    auto c =  eve::zero_; 
    wide<Type,T>  lhs([](int i, int c) { return i%2 ? 0 : 1; }); 
    wide<Type,T>  rhs1([](int i, int  ) { return (i%2)*i; })
      , ref([c](int i, int ) { return eve::if_else(Type(i%2 ? 0 : 1), Type((i%2)*i), c); })
      , refs([c](int i, int ) { return eve::if_else(Type(i%2 ? 0 : 1), Type(2), c); }); 

    TTS_SECTION( "supports eve::if_else on wide+zero" )
    {
      if constexpr(std::is_integral_v<Type>)
      {
        TTS_EQUAL(ref, eve::if_else(lhs, rhs1, c));
        TTS_EQUAL(refs, eve::if_else(lhs, Type(2), c));
        TTS_EQUAL(ref, eve::if_else(eve::is_nez(lhs), rhs1, c));
        TTS_EQUAL(refs, eve::if_else(eve::is_nez(lhs), Type(2), c));
      }
      else
      {
        TTS_IEEE_EQUAL(ref, eve::if_else(lhs, rhs1, c));
        TTS_IEEE_EQUAL(refs, eve::if_else(lhs, Type(2), c));
        TTS_IEEE_EQUAL(ref, eve::if_else(eve::is_nez(lhs), rhs1, c));
        TTS_IEEE_EQUAL(refs, eve::if_else(eve::is_nez(lhs), Type(2), c));
      }
    }
  } 
}
#endif
