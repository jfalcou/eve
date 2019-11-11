//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::pedantic_(eve::maxmag) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::maxmag)(Type(0)  , Type(0) ) , (Type));
  TTS_EXPR_IS(eve::pedantic_(eve::maxmag)(Value(0) , Type(0) ) , (Type));
  TTS_EXPR_IS(eve::pedantic_(eve::maxmag)(Type(0)  , Value(0)) , (Type));
}

TTS_CASE("Check eve::pedantic_(eve::maxmag) behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Type(0)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Type(0)), (Type(1))), (Type(1)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Type(1)), (Type(0))), (Type(1)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Type(1)), (Type(1))), (Type(1)));

  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Value(0)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Value(0)), (Type(1))), (Type(1)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Value(1)), (Type(0))), (Type(1)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Value(1)), (Type(1))), (Type(1)));

  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Type(0)), (Value(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Type(0)), (Value(1))), (Type(1)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Type(1)), (Value(0))), (Type(1)));
  TTS_EQUAL(eve::pedantic_(eve::maxmag)((Type(1)), (Value(1))), (Type(1)));

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::maxmag)((eve::Nan<Type>() ), (Type(1))) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::maxmag)((eve::Nan<Value>()), (Type(1))) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::maxmag)((eve::Nan<Type>() ), (Value(1))), (eve::Nan<Type>()) );

    TTS_IEEE_EQUAL(eve::pedantic_(eve::maxmag)((Type(1)) , (eve::Nan<Type>())  ), (Type(1)) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::maxmag)((Value(1)), (eve::Nan<Type>())  ), (Type(1)) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::maxmag)((Type(1)) , (eve::Nan<Value>()) ), (Type(1)) );
  }

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Type>(-1), (Type(2))), (Type(2)));
    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Type>(-2), (Type(1))), static_cast<Type>(-2));
    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Type>(-2), (Type(2))), (Type(2)));

    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Type>(-1), (Value(2))), (Type(2)));
    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Type>(-2), (Value(1))), static_cast<Type>(-2));
    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Type>(-2), (Value(2))), (Type(2)));

    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Value>(-1), (Type(2))), (Type(2)));
    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Value>(-2), (Type(1))), static_cast<Type>(-2));
    TTS_EQUAL(eve::pedantic_(eve::maxmag)(static_cast<Value>(-2), (Type(2))), (Type(2)));
  }
}
