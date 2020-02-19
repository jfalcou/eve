//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fma.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check eve::fma return type")
{
  TTS_EXPR_IS(eve::numeric_(eve::fma)(Type(), Type(), Type()), (Type));
}

TTS_CASE("Check eve::numeric_(eve::fma) behavior")
{
  TTS_EQUAL(eve::numeric_(eve::fma)(Type(0), Type(0), Type(0)), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::fma)(Type(0), Type(0), Type(7)), (Type(7)));
  TTS_EQUAL(eve::numeric_(eve::fma)(Type(2), Type(0), Type(7)), (Type(7)));
  TTS_EQUAL(eve::numeric_(eve::fma)(Type(0), Type(5), Type(7)), (Type(7)));
  TTS_EQUAL(eve::numeric_(eve::fma)(Type(2), Type(5), Type(7)), (Type(17)));
  if constexpr(std::is_floating_point_v<Value>)
  {
    Type e = eve::Eps<Type>();
    TTS_EQUAL(eve::numeric_(eve::fma)(eve::inc(e), eve::oneminus(e), eve::Mone<Type>()), (-eve::sqr(e)));
    TTS_EQUAL(                        (eve::inc(e)* eve::oneminus(e)+ eve::Mone<Type>()) , eve::Zero<Type>());
    TTS_EQUAL(eve::numeric_(eve::fma)(eve::Valmax<Type>(), Type(2), eve::Valmin<Type>()), eve::Valmax<Type>());
    TTS_EQUAL(                       (eve::Valmax<Type>()* Type(2)+ eve::Valmin<Type>()), eve::Inf<Type>()); 
  }
  
}
