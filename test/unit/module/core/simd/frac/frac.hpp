//==================================================================================================
/**
  EVE - Expressive Vector Engine
<<<<<<< HEAD
  Copyright 2019 Joel FALCOU 
=======
  Copyright 2019 JeaJoel FALCOU 
>>>>>>> frac
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef FRAC_HPP
#define FRAC_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/frac.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/wide.hpp>
#include <type_traits>

using eve::fixed;
 
TTS_CASE_TPL("Check frac behavior on wide",
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
  
  wide<Type, T> lhs([](int i, int) { return Type(i%2 ? (i+2) :-i-2)/3; }),
                ref([](int i, int) { return eve::frac(Type(i%2 ? i+2 :-i-2)/3); });
  
  TTS_EQUAL(ref, eve::frac(lhs));
   
}

#endif
