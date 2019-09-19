//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

using Type = float;
#include "horn1.hpp"
TTS_CASE("Check eve::horn1 behavior") 
{
  using eve::detail::horn1; 
  TTS_EQUAL((horn1<Type,0x0U>(Type(0))), Type(0));
  TTS_EQUAL((horn1<Type, 0x3f800000U, 0x00000000U, 0x3f800000U>(Type(1))), Type(3));
  TTS_EQUAL((horn1<Type, 0x40000000U, 0x3f800000U, 0x3f800000U>(Type(2))), Type(16));  
}

