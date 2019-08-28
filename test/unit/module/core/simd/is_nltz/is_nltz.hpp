//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NLTZ_HPP
#define IS_NLTZ_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_nltz.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_nltz behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::logical;

  wide<Type, T>           lhs([](auto i, auto) { return Type(i%2); });
  logical<wide<Type, T>>  ref([](auto i, auto) { return eve::is_nltz(Type(i%2)); }); 
  TTS_EQUAL(ref, eve::is_nltz(lhs));
  if constexpr(std::is_signed_v<Type>)
  {
    wide<Type, T>           lhs([](auto i, auto) { return Type(i%3 ? i%2 : -i%2); });
    logical<wide<Type, T>>  ref([](auto i, auto) { return eve::is_nltz(Type(i%3 ? i%2 : -i%2)); });
    
    TTS_EQUAL(ref, eve::is_nltz(lhs));
  }
  
  TTS_EQUAL(ref, eve::is_nltz(lhs));
}

TTS_CASE_TPL("Check is_nltz behavior on logical<wide>",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
             )
{
  using eve::wide;
  using eve::logical;

  logical<wide<Type, T>> lhs([](auto i, auto) { return (i%2) > 0; });
  logical<wide<Type, T>> ref([](auto i, auto) { return eve::is_nltz( i%2 > 0 ); });

  TTS_EQUAL(ref, eve::is_nltz(lhs));
}

#endif
