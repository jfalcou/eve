//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef ATAN2PI_HPP
#define ATAN2PI_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/atan2pi.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check atan2pi behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>, 
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

   wide<Type, T>  lhs([](auto i, auto) { return Type(i); }),
     rhs([](auto i, auto c) { return Type(c-i); }), 
     ref([](auto i, auto c) { return eve::atan2pi(Type(i), Type(c-i)); }); 
   wide<Type, T> val = eve::atan2pi(lhs, rhs);
   TTS_ULP_EQUAL(val, ref, 11.5); 
}

#endif
