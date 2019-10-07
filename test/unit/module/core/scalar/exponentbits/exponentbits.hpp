//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXPONENTBITS_HPP
#define EXPONENTBITS_HPP

#include <eve/function/scalar/exponentbits.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

TTS_CASE("Check exponentbits return type") { TTS_EXPR_IS(eve::exponentbits(Type(0)), eve::detail::as_integer_t<Type>); }

TTS_CASE ("checking  exponentbits behaviour")
{
 
  if constexpr(std::is_same_v<Type, float>)
  {
    for(int i=1, k = 0; i < 10; i*= 2, ++k)
    {
      TTS_EQUAL(1065353216+k*8388608, eve::exponentbits(Type(i)));
    }
  }
  else
  {
    for(int i=1, k = 0; i < 10; i*= 2, ++k)
    {
      TTS_EQUAL(4607182418800017408ll+k*4503599627370496ll, eve::exponentbits(Type(i)));
   }
  }
}

#endif
