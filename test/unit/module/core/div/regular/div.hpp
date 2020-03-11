//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check eve::div return type")
{
  TTS_EXPR_IS(eve::div(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::div behavior")
{
  TTS_EQUAL(eve::div(EVE_TYPE( 0), EVE_TYPE(1)), (EVE_TYPE(0  )));
  TTS_EQUAL(eve::div(EVE_TYPE( 1), EVE_TYPE(1)), (EVE_TYPE(1  )));
  TTS_EQUAL(eve::div(EVE_TYPE(12), EVE_TYPE(4)), (EVE_TYPE(3  )));
  TTS_EQUAL(eve::div(EVE_TYPE( 1), EVE_TYPE(2)), (EVE_TYPE(0.5)));
  
  TTS_EQUAL(eve::div(EVE_VALUE( 0), EVE_TYPE(1)), (EVE_TYPE(0  )));
  TTS_EQUAL(eve::div(EVE_VALUE( 1), EVE_TYPE(1)), (EVE_TYPE(1  )));
  TTS_EQUAL(eve::div(EVE_VALUE(12), EVE_TYPE(4)), (EVE_TYPE(3  )));
  TTS_EQUAL(eve::div(EVE_VALUE( 1), EVE_TYPE(2)), (EVE_TYPE(0.5)));
  
  TTS_EQUAL(eve::div(EVE_TYPE( 0), EVE_VALUE(1)), (EVE_TYPE(0  )));
  TTS_EQUAL(eve::div(EVE_TYPE( 1), EVE_VALUE(1)), (EVE_TYPE(1  )));
  TTS_EQUAL(eve::div(EVE_TYPE(12), EVE_VALUE(4)), (EVE_TYPE(3  )));
  TTS_EQUAL(eve::div(EVE_TYPE( 1), EVE_VALUE(2)), (EVE_TYPE(0.5)));
  
  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    using i_t =  eve::detail::as_integer_t<EVE_VALUE>; 
    TTS_EQUAL(eve::div(eve::Valmax<EVE_TYPE>(), EVE_TYPE(2)), EVE_TYPE(eve::Valmax<i_t>() >> 1));
    TTS_EQUAL(eve::div(eve::Valmax<EVE_VALUE>(), EVE_TYPE(2)), EVE_TYPE(eve::Valmax<i_t>() >> 1));
    TTS_EQUAL(eve::div(eve::Valmax<EVE_TYPE>(), EVE_VALUE(2)), EVE_TYPE(eve::Valmax<i_t>() >> 1));  

    TTS_EQUAL(eve::div(eve::Valmax<EVE_TYPE>(), EVE_TYPE(1)), EVE_TYPE(eve::Valmax<i_t>())); 
    TTS_EQUAL(eve::div(eve::Valmax<EVE_VALUE>(), EVE_TYPE(1)), EVE_TYPE(eve::Valmax<i_t>()));
    TTS_EQUAL(eve::div(eve::Valmax<EVE_TYPE>(), EVE_VALUE(1)), EVE_TYPE(eve::Valmax<i_t>()));  
  }
  
  if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::div(EVE_TYPE(-1), EVE_TYPE(1)) , (EVE_TYPE(-1)));
    TTS_EQUAL(eve::div(EVE_TYPE(-6), EVE_TYPE(-2)), (EVE_TYPE( 3)));
    
    TTS_EQUAL(eve::div(EVE_VALUE(-1), EVE_TYPE(1)) , (EVE_TYPE(-1)));
    TTS_EQUAL(eve::div(EVE_VALUE(-6), EVE_TYPE(-2)), (EVE_TYPE( 3)));
    
    TTS_EQUAL(eve::div(EVE_TYPE(-1), EVE_VALUE(1)) , (EVE_TYPE(-1)));
    TTS_EQUAL(eve::div(EVE_TYPE(-6), EVE_VALUE(-2)), (EVE_TYPE( 3)));
  }
}
