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

using eve::fixed;

TTS_CASE_TPL( "Check abs behavior on wide",
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
  using eve::detail::horn1; 
  using t_t = wide < Type, T>; 
  if constexpr(std::is_same_v<Type, float>)
  {
    TTS_EQUAL((horn1<t_t,0x0U>(t_t(0))), t_t(0));
    TTS_EQUAL((horn1<t_t, 0x3f800000U, 0x00000000U, 0x3f800000U>(t_t(1))), t_t(3));
    TTS_EQUAL((horn1<t_t, 0x40000000U, 0x3f800000U, 0x3f800000U>(t_t(2))), t_t(16));  
  }
  else                        
  {
    TTS_EQUAL((horn1<t_t,0x0ULL>(t_t(0))), t_t(0));
    TTS_EQUAL((horn1<t_t, 0x3FF0000000000000ULL, 0x00000000ULL, 0x3FF0000000000000ULL>(t_t(1))), t_t(3));
    TTS_EQUAL((horn1<t_t, 0x4000000000000000ULL, 0x00000000ULL, 0x3FF0000000000000ULL>(t_t(2))), t_t(14));  
  }
  
}

#endif
