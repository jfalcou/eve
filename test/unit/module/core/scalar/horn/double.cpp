//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

using Type = double; 
#include "horn.hpp"
TTS_CASE("Check eve::horn behavior")
{
  using eve::detail::horn;
  TTS_EQUAL((horn<Type,0x0ULL>(Type(0))), Type(0));
  TTS_EQUAL((horn<Type, 0x3FF0000000000000ULL, 0x00000000ULL, 0x3FF0000000000000ULL>(Type(1))), Type(2));
  TTS_EQUAL((horn<Type, 0x4000000000000000ULL, 0x00000000ULL, 0x3FF0000000000000ULL>(Type(2))), Type(6));  
}
