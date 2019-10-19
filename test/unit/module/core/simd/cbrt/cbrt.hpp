//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CBRT_HPP
#define CBRT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/cbrt.hpp>
#include <eve/wide.hpp>
#include <eve/function/load.hpp>
#include <eve/detail/meta.hpp>
#include <cmath>

using eve::fixed;

TTS_CASE_TPL("Check raw_(cbrt) behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;
  using t_t =  wide<Type, T>;
  Type tmp = 1; 
  t_t lhs([&tmp](auto,  auto){tmp*= 50; return tmp; });
  tmp = 1; 
  t_t ref([&tmp](auto,  auto){tmp*= 50;  return std::cbrt(tmp); }); 
  TTS_ULP_EQUAL(eve::cbrt(lhs),  ref, 1.0); 
          
            
}


#endif
