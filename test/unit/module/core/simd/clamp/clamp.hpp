//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CLAMP_HPP
#define CLAMP_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/clamp.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check clamp behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> arg0([](auto i, auto  ) { return Type(i+2); }),
    arg1([](auto i, auto ) { return Type(i); }),
    arg2([](auto i, auto ) { return Type(2*i); }),
    ref ([](auto i, auto ) { return eve::clamp(Type(i+2), Type(i), Type(2*i)); });
//   std::cout << "arg0 " << arg0 << std::endl;
//   std::cout << "lo   " << arg1 << std::endl;
//   std::cout << "hi   " << arg2 << std::endl;
//   std::cout << "r    " << eve::clamp(arg0, arg1, arg2) << std::endl;
//   std::cout << "ref  " << ref << std::endl;
  TTS_EQUAL(ref, eve::clamp(arg0, arg1, arg2));
}

TTS_CASE_TPL("Check clamp behavior on wide + scalar",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using eve::clamp; 

  wide<Type, T> arg0([](auto i, auto  ) { return i; }),
    arg1([](auto i, auto ) { return i+2; }),
    arg2([](auto i, auto c) { return c + i+2; }),
    refvvs ([](auto i, auto c) { return clamp(Type(i), Type(i+2), Type(100)); }),
    refvss ([](auto i, auto c) { return clamp(Type(i), Type(10), Type(100)); }),     
    refvsv ([](auto i, auto c) { return  clamp(Type(i), Type(0), Type(c+i+2)); }); 
// //     refsvs ([](auto i, auto c) { return 5*c + 4; }),
// //     refssv ([](auto i, auto c) { return 5*10 + (c-i); }),
// //     refsvv ([](auto i, auto c) { return 5*c + (c-i); });

  TTS_EQUAL(refvvs, eve::clamp(arg0, arg1 ,Type( 100)   ));
  TTS_EQUAL(refvss, eve::clamp(arg0, Type(10)   , Type(100)   ));
  TTS_EQUAL(refvsv, eve::clamp(arg0, Type( 0)   , arg2));
// //   TTS_EQUAL(refsvs, eve::clamp(5   , arg1 , 4   ));
// //   TTS_EQUAL(refssv, eve::clamp(5   , 10   , arg2));
// //   TTS_EQUAL(refsvv, eve::clamp(5   , arg1 , arg2));
}

#endif
