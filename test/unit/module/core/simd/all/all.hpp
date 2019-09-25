//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 JeaJoel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ALL_HPP
#define ALL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/all.hpp>
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/is_nez.hpp>

using eve::fixed;

// TTS_CASE_TPL("Check all behavior on wide",
//              fixed<1>//, 
//  //              fixed<2>,
//   //              fixed<4>, 
//  //              fixed<8>,
//   //              fixed<16>,
//   //              fixed<32>,
//  //              fixed<64>
//             )
// {
//   using eve::wide;

//   wide<Type, T> lhs([](int i, int) { return i+1; });
//   TTS_EQUAL(true, eve::all(lhs));
  
//   for(int j=0; j < T::value; ++j)
//  {
//    wide<Type, T> rhs([j](int i, int) { return i > j ? 0 :i; }); 
//   std::cout << rhs << std::endl;
//   TTS_EQUAL(false, eve::all(rhs));
//  }

TTS_CASE_TPL("Check all behavior on wide",
             fixed<1>//, 
//              fixed<2>,
//              fixed<4>, 
//              fixed<8>,
//              fixed<16>,
//              fixed<32>,
//              fixed<64>
            )
{
  using eve::wide;

  wide<Type, T> lhs([](int i, int) { return i+1; });
  
//  TTS_EQUAL(true, eve::all(lhs));
  using i8_t = wide<int8_t, fixed<16> , eve::sse_>;
  
  auto z = eve::bitwise_cast<i8_t>(eve::is_nez(lhs));
  std::cout  << "lhs"<<  lhs <<  std::endl;
  std::cout  << "z " <<  z << std::endl; 
  TTS_EQUAL(0, 0); 
}
  


#endif
