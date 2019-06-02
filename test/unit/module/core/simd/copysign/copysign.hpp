//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry LAPRESTE
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COPYSIGN_HPP
#define COPYSIGN_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/copysign.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;

TTS_CASE_TPL("Check copysign behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  if constexpr(std::is_signed_v<Type>)
  {
      auto N = T::value; 
      wide<Type, T> a1([](auto i,  auto ){ return (i%2) ? Type(i) : Type(-i); }), 
        a2([N](auto i,  auto ){ return (i%2) ? Type(i+N) : Type(-(i+N)); }), 
        b([N](auto i,  auto ){ return eve::copysign((i%2) ? Type(i) : Type(-(i)),
                                             (i%2) ? Type(i+N) : Type(-(i+N))); }); 
      TTS_IEEE_EQUAL(eve::copysign(a1, a2), b);
  }
  else
  {
    auto N = T::value; 
    wide<Type, T> a1([](auto i,  auto ){ return i; }), 
      a2([N](auto i,  auto ){ return i%2; }), 
      b([N](auto i,  auto ){ return eve::copysign(Type(i), Type(i%2)); }); 
    TTS_EQUAL(eve::copysign(a1, a2), b);
  }
}

#endif
