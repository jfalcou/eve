//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/floor2.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check floor2 return type")
{
  TTS_EXPR_IS(eve::floor2(Type()), (Type));
}

TTS_CASE("Check eve::floor2 behavior")
{
  if constexpr(!std::is_floating_point_v<Value>)
  {
    using i_t =  eve::detail::as_integer_t<Value, signed>; 
    int64_t z = eve::Valmax<i_t>(); 
    for(int64_t i=0,  j = 0; i < z && j < 1000; i+= z/100+1, ++j)
    {
      TTS_EQUAL(eve::floor2(Type(i)), i ?Type(double(std::exp2l(std::floor(std::log2l(i))))) : Type(0));
    }
    for(int64_t i=z/16; i > 1; i/= 2)
    {
      TTS_EQUAL(eve::floor2(Type(i)), Type(std::exp2l(std::floor(std::log2l(i)))));
    }
  }
  else  
  {
    TTS_EQUAL(eve::floor2(Type(0))   , Type(0)); 
    TTS_EQUAL(eve::floor2(Type(1.3)) , Type(1));
    TTS_EQUAL(eve::floor2(Type(1.5)) , Type(1));
    TTS_EQUAL(eve::floor2(Type(1.6)) , Type(1));
    TTS_EQUAL(eve::floor2(Type(2.9)) , Type(2));
  }
}
