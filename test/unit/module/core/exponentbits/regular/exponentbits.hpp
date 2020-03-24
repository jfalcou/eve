//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/exponentbits.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>

TTS_CASE("Check exponentbits return type") {
  TTS_EXPR_IS((eve::exponentbits(EVE_TYPE(0))), (eve::detail::as_integer_t<EVE_TYPE>));
}

TTS_CASE ("checking  exponentbits behaviour")
{
  if constexpr(std::is_same_v<EVE_VALUE, float>)
  {
    using i_t = eve::detail::as_integer_t<EVE_TYPE>; 
    for(int i=1, k = 0; i < 10; i*= 2, ++k)
    {
      TTS_EQUAL(i_t(1065353216+k*8388608), eve::exponentbits(EVE_TYPE(i)));
    }
  }
  else
  {
    using i_t = eve::detail::as_integer_t<EVE_TYPE>; 
    for(int i=1, k = 0; i < 10; i*= 2, ++k)
    {
      TTS_EQUAL(i_t(4607182418800017408ll+k*4503599627370496ll), eve::exponentbits(EVE_TYPE(i)));
   }
  }
}



