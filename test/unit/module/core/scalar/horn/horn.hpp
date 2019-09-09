//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef HORN_HPP
#define HORN_HPP

#include <eve/module/core/detail/generic/horn.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::horn behavior")
{
  using eve::detail::horn; 
  TTS_EQUAL((horn<Type,0x0>(Type(0))), Type(0));
  if constexpr(std::is_same_v<Type, float>)
  {
    TTS_EQUAL((horn<Type, 0x3f800000UL, 0x00000000UL, 0x3f800000UL>(Type(1))), Type(2));
    TTS_EQUAL((horn<Type, 0x40000000UL, 0x3f800000UL, 0x3f800000UL>(Type(2))), Type(8));  
  }
  else                        
  {
    TTS_EQUAL((horn<Type, 0x3FF0000000000000ULL, 0x00000000ULL, 0x3FF0000000000000ULL>(Type(1))), Type(2));
    TTS_EQUAL((horn<Type, 0x4000000000000000ULL, 0x00000000ULL, 0x3FF0000000000000ULL>(Type(2))), Type(6));  
  }
  
}


#endif
