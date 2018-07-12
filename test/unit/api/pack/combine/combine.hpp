//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COMBINE_HPP
#define COMBINE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/pack.hpp>
#include <eve/function/combine.hpp>

using eve::fixed;

TTS_CASE( "Check combining for arithmetic values" )
{
  using eve::pack;

  pack<Type,fixed<2>> ref(13,37);

  TTS_EQUAL( (eve::combine(Type(13),Type(37))), ref );
}

TTS_CASE_TPL( "Check combining for arithmetic pack"
            , fixed<1>,fixed<2>,fixed<4>,fixed<8>,fixed<16>,fixed<32>,fixed<64>
            )
{
  using eve::pack;

  pack<Type,T> low ( [](auto i, auto) { return 1+i; } );
  pack<Type,T> high( [](auto i, auto) { return T::value+1+i; } );
  pack<Type,typename T::combined_type> ref( [](auto i, auto) { return 1+i; } );

  TTS_EQUAL( (pack<Type,typename T::combined_type>(low,high)) , ref  );
  TTS_EQUAL( (eve::combine(low,high)), ref );
}

#endif
