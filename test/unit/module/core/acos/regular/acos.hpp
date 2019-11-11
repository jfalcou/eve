//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acos.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check acos return type")
{
  TTS_EXPR_IS(eve::acos(Type(0)), (Type));
}

TTS_CASE("Check eve::acos behavior")
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acos(Type(2)) , eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::acos(Type(-2)), eve::Nan<Type>(), 0);
  }

  TTS_ULP_EQUAL(eve::acos(Type( 0.5)) , eve::Pi<Type>()/3   , 0.5 );
  TTS_ULP_EQUAL(eve::acos(Type(-0.5)) , 2*eve::Pi<Type>()/3 , 0.5 );
  TTS_ULP_EQUAL(eve::acos(Type(-1. )) , eve::Pi<Type>()     , 0   );
  TTS_ULP_EQUAL(eve::acos(Type( 1. )) , Type(0)             , 0   );
  TTS_ULP_EQUAL(eve::acos(Type( 0. )) , eve::Pio_2<Type>()  , 0   );

  TTS_EXPECT( all(eve::is_positive(eve::acos(Type(1)))) );

  TTS_ULP_EQUAL(eve::acos(Type(8.414715528e-01)), Type(std::acos(Value(8.414715528e-01))), 1.5 );
  TTS_ULP_EQUAL(eve::acos(Type(9.689134359e-01)), Type(std::acos(Value(9.689134359e-01))), 4.0 );
  TTS_ULP_EQUAL(eve::acos(Type(9.922192097e-01)), Type(std::acos(Value(9.922192097e-01))), 7.5 );
  TTS_ULP_EQUAL(eve::acos(Type(9.995127916e-01)), Type(std::acos(Value(9.995127916e-01))), 26.5);
  TTS_ULP_EQUAL(eve::acos(Type(9.998779893e-01)), Type(std::acos(Value(9.998779893e-01))), 44.5);
  TTS_ULP_EQUAL(eve::acos(Type(9.999695420e-01)), Type(std::acos(Value(9.999695420e-01))), 142);
  TTS_ULP_EQUAL(eve::acos(Type(9.999927878e-01)), Type(std::acos(Value(9.999927878e-01))), 234 );
  TTS_ULP_EQUAL(eve::acos(Type(9.999984503e-01)), Type(std::acos(Value(9.999984503e-01))), 361.5);
  TTS_ULP_EQUAL(eve::acos(Type(9.999996424e-01)), Type(std::acos(Value(9.999996424e-01))), 867.5);
  TTS_ULP_EQUAL(eve::acos(Type(9.999999404e-01)), Type(std::acos(Value(9.999999404e-01))), 1643.5);
}
