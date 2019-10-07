//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REDUCE_FAST_HPP
#define REDUCE_FAST_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/reduce_fast.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check reduce_fast behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;
  
  wide<Type, T> lhs([](auto i, auto) { return Type(2*i+3); }); 
  Type sn[T::value], sx[T::value], z; 
  for(int i=0; i < T::value; i++)
  {
    std::tie(sn[i], sx[i], z) = eve::reduce_fast(Type(2*i+3));
  }
  wide<Type, T> refn([sn](auto i, auto){ return sn[i]; } );
  wide<Type, T> refx([sx](auto i, auto){ return sx[i]; } );
  std::cout << "lhs " << lhs << std::endl; 
  auto [n, x] =  eve::reduce_fast(lhs);
  TTS_EQUAL(refn, n);
  TTS_EQUAL(refx, x); 
  
  
}

#endif
 
