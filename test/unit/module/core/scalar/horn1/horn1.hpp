//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef HORN1_HPP
#define HORN1_HPP

#include <eve/module/core/detail/generic/horn1.hpp>
#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/abs.hpp>
#include <eve/wide.hpp>


TTS_CASE("Check eve::horn1 behavior")
{
  using eve::detail::horn1; 
  TTS_EQUAL((horn1<Type,0x0>(Type(0))), Type(0));
  if constexpr(std::is_same_v<Type, float>)
  {
    TTS_EQUAL((horn1<Type, 0x3f800000, 0x00000000, 0x3f800000>(Type(1))), Type(3));
    TTS_EQUAL((horn1<Type, 0x40000000, 0x3f800000, 0x3f800000>(Type(2))), Type(16));  
  }
  else                        
  {
    TTS_EQUAL((horn1<Type, 0x3FF0000000000000, 0x00000000, 0x3FF0000000000000>(Type(1))), Type(3));
    TTS_EQUAL((horn1<Type, 0x4000000000000000, 0x00000000, 0x3FF0000000000000>(Type(2))), Type(14));  
  }
  
}


#endif
