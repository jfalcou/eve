//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fnma.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check eve::fnma return type")
{
  TTS_EXPR_IS(eve::numeric_(eve::fnma)(Type(), Type(), Type()), (Type));
}

TTS_CASE("Check eve::numeric_(eve::fnma) behavior")
{
  TTS_EQUAL(eve::numeric_(eve::fnma)(Type(0), Type(0), Type(0)), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::fnma)(Type(0), Type(0), Type(7)), (Type(7)));
  TTS_EQUAL(eve::numeric_(eve::fnma)(Type(2), Type(0), Type(7)), (Type(7)));
  TTS_EQUAL(eve::numeric_(eve::fnma)(Type(0), Type(5), Type(7)), (Type(7)));
  TTS_EQUAL(eve::numeric_(eve::fnma)(Type(-2), Type(5), Type(7)), (Type(17)));
  if constexpr(std::is_floating_point_v<Value>)
  {
    Type e = eve::Eps<Type>();
    TTS_EQUAL(eve::numeric_(eve::fnma)(eve::inc(e), eve::oneminus(e), eve::One<Type>()), (eve::sqr(e)));
    TTS_EQUAL(eve::numeric_(eve::fnma)(eve::Valmax<Type>(), Type(2), eve::Valmax<Type>()), -eve::Valmax<Type>());
  }
  
}
