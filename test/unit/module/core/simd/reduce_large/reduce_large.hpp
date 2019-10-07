//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef REDUCE_LARGE_HPP
#define REDUCE_LARGE_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/reduce_large.hpp>
#include <eve/function/simd/rem_pio2.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <tuple>

using eve::fixed;

TTS_CASE_TPL("Check reduce_large behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::logical;
  using eve::wide;
  
  wide<Type, T> lhs([](auto i, auto) { return Type(200*i+3); }); 
  Type sn[T::value], sx[T::value], dsx[T::value]; 
  for(int i=0; i < T::value; i++)
  {
    std::tie(sn[i], sx[i], dsx[i]) = eve::reduce_large(Type(200*i+3));
  }
  wide<Type, T> refn([sn](auto i, auto){ return sn[i]; } );
  wide<Type, T> refx([sx](auto i, auto){ return sx[i]; } );
  wide<Type, T> refdx([dsx](auto i, auto){ return dsx[i]; } );     
  std::cout << "lhs " << lhs << std::endl; 
  auto [n, x, dx] =  eve::reduce_large(lhs);
  auto [nn, xx] =  eve::rem_pio2(lhs);
  std::cout << "n " << n << std::endl; 
  std::cout << "nn " << nn << std::endl; 
   std::cout << "x " << x << std::endl; 
  std::cout << "xx " << xx << std::endl;
  std::cout << "dx" << dx << std::endl;    
  
  TTS_EQUAL(nn, n);
  TTS_EQUAL(xx, x); 
  
  
}

#endif
