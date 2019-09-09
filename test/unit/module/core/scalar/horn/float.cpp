//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

using Type = float;
#include "horn.hpp"
TTS_CASE("Check eve::horn behavior")
{
  using eve::detail::horn;
  TTS_EQUAL((horn<Type,std::uint32_t(0x0U)>(Type(0))), Type(0));
  TTS_EQUAL((horn<Type, 0x3f800000, 0x00000000, 0x3f800000>(Type(1))), Type(2));
  TTS_EQUAL((horn<Type, 0x40000000, 0x3f800000, 0x3f800000>(Type(2))), Type(8));  
}

  
