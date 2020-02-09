//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/min.hpp>
#include <eve/function/numeric.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <tts/tests/basic.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::pedantic_(eve::min) return type")
{
  TTS_EXPR_IS(eve::pedantic_(eve::min)(Type(0)  , Type(0) ) , (Type));
  TTS_EXPR_IS(eve::pedantic_(eve::min)(Value(0) , Type(0) ) , (Type));
  TTS_EXPR_IS(eve::pedantic_(eve::min)(Type(0)  , Value(0)) , (Type));
}

TTS_CASE("Check eve::pedantic_(eve::min) behavior")
{
  TTS_EQUAL(eve::pedantic_(eve::min)((Type(0)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Type(0)), (Type(1))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Type(1)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Type(1)), (Type(1))), (Type(1)));

  TTS_EQUAL(eve::pedantic_(eve::min)((Value(0)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Value(0)), (Type(1))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Value(1)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Value(1)), (Type(1))), (Type(1)));

  TTS_EQUAL(eve::pedantic_(eve::min)((Type(0)), (Value(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Type(0)), (Value(1))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Type(1)), (Value(0))), (Type(0)));
  TTS_EQUAL(eve::pedantic_(eve::min)((Type(1)), (Value(1))), (Type(1)));

  if constexpr(std::is_floating_point_v<Value>)
  {
    TTS_IEEE_EQUAL(eve::pedantic_(eve::min)((eve::Nan<Type>() ), (Type(1))) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::min)((eve::Nan<Value>()), (Type(1))) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::min)((eve::Nan<Type>() ), (Value(1))), (eve::Nan<Type>()) );

    TTS_IEEE_EQUAL(eve::pedantic_(eve::min)((Type(1)) , (eve::Nan<Type>())  ), (Type(1)) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::min)((Value(1)), (eve::Nan<Type>())  ), (Type(1)) );
    TTS_IEEE_EQUAL(eve::pedantic_(eve::min)((Type(1)) , (eve::Nan<Value>()) ), (Type(1)) );

    TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic_(eve::min)(eve::Mzero<Type>(), eve::Zero<Type>()))));
    TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic_(eve::min)(eve::Zero<Type>(), eve::Mzero<Type>()))));    
  }
}
