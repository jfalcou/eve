//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fnms.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/zero.hpp>

TTS_CASE("Check eve::fnms return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::fnms)(Type(), Type(), Type()), (Type));
}

TTS_CASE("Check eve::pedantic_(eve::fnms) behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::fnms)(Type(0), Type(0), Type(0)), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::fnms)(Type(0), Type(0), Type(7)), (Type(-7)));
  TTS_EQUAL(eve::pedantic_(eve::fnms)(Type(2), Type(0), Type(7)), (Type(-7)));
  TTS_EQUAL(eve::pedantic_(eve::fnms)(Type(0), Type(5), Type(7)), (Type(-7)));
  TTS_EQUAL(eve::pedantic_(eve::fnms)(Type(2), Type(5), Type(7)), (Type(-17)));
  if constexpr(std::is_floating_point_v<Value>)
  {
    Type e = eve::Eps<Type>();
    TTS_EQUAL(eve::pedantic_(eve::fnms)(eve::inc(e), eve::dec(e), eve::One<Type>()), -(eve::sqr(e)));
  }
  
}
