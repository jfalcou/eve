//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/minmag.hpp>
#include <eve/function/numeric.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::numeric_(eve::minmag) return type")
{
  TTS_EXPR_IS(eve::numeric_(eve::minmag)(Type(0)  , Type(0) ) , (Type));
  TTS_EXPR_IS(eve::numeric_(eve::minmag)(Value(0) , Type(0) ) , (Type));
  TTS_EXPR_IS(eve::numeric_(eve::minmag)(Type(0)  , Value(0)) , (Type));
}

TTS_CASE("Check eve::numeric_(eve::minmag) behavior")
{
  TTS_EQUAL(eve::numeric_(eve::minmag)((Type(0)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Type(0)), (Type(1))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Type(1)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Type(1)), (Type(1))), (Type(1)));

  TTS_EQUAL(eve::numeric_(eve::minmag)((Value(0)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Value(0)), (Type(1))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Value(1)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Value(1)), (Type(1))), (Type(1)));

  TTS_EQUAL(eve::numeric_(eve::minmag)((Type(0)), (Value(0))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Type(0)), (Value(1))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Type(1)), (Value(0))), (Type(0)));
  TTS_EQUAL(eve::numeric_(eve::minmag)((Type(1)), (Value(1))), (Type(1)));

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_IEEE_EQUAL(eve::numeric_(eve::minmag)((eve::Nan<Type>() ), (Type(1)))  , (Type(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::minmag)((eve::Nan<Value>()), (Type(1)))  , (Type(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::minmag)((eve::Nan<Type>() ), (Value(1))) , (Type(1)) );

    TTS_IEEE_EQUAL(eve::numeric_(eve::minmag)((Type(1))  , (eve::Nan<Type>())  ), (Type(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::minmag)((Value(1)) , (eve::Nan<Type>())  ), (Type(1)) );
    TTS_IEEE_EQUAL(eve::numeric_(eve::minmag)((Type(1))  , (eve::Nan<Value>()) ), (Type(1)) );
  }

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-3), (Type(2))), (Type(2)));
    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-1), (Type(2))), static_cast<Type>(-1));
    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-2), (Type(2))), static_cast<Type>(-2));

    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-3), (Type(2))), (Type(2)));
    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-1), (Type(2))), static_cast<Type>(-1));
    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-2), (Type(2))), static_cast<Type>(-2));

    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-3), (Type(2))), (Type(2)));
    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-1), (Type(2))), static_cast<Type>(-1));
    TTS_EQUAL(eve::numeric_(eve::minmag)(static_cast<Type>(-2), (Type(2))), static_cast<Type>(-2));
  }
}
