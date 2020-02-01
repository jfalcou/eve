//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/ceil2.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>
#include <cmath>

TTS_CASE("Check ceil2 return type")
{
  TTS_EXPR_IS(eve::ceil2(Type()), (Type));
}

TTS_CASE("Check eve::ceil2 behavior")
{
  if constexpr(!std::is_floating_point_v<Value>)
  {
    using i_t =  eve::detail::as_integer_t<Value, signed>; 
    int64_t z = eve::Valmax<i_t>()/2; 
    for(int64_t i=0; i < z; i+= z/100+1)
    {
      TTS_EQUAL(eve::ceil2(Type(i)), Type(double(std::exp2l(std::ceil(std::log2l(i))))));
    }
    for(int64_t i=z+1; i > 0; i/= 2)
    {
      TTS_EQUAL(eve::ceil2(Type(i)), Type(std::exp2l(std::ceil(::log2l(i)))));
    }
  }
  else  
  {
    TTS_EQUAL(eve::ceil2(Type(0))   , Type(0)); 
    TTS_EQUAL(eve::ceil2(Type(1.3)) , Type(2));
    TTS_EQUAL(eve::ceil2(Type(1.5)) , Type(2));
    TTS_EQUAL(eve::ceil2(Type(1.6)) , Type(2));
    TTS_EQUAL(eve::ceil2(Type(2.9)) , Type(4));
  }
}
