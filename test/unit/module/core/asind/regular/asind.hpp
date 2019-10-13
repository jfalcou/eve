//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asind.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::asind return type")
{
  TTS_EXPR_IS(eve::asind(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::asind behavior")
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asind(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::asind(Type(2))          , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::asind(Type(-2))         , (eve::Nan<Type>()) );
  }

  TTS_ULP_EQUAL(eve::asind(Type( 0.5)) ,  (Type(30))  , 0.5);
  TTS_ULP_EQUAL(eve::asind(Type(-0.5)) ,  (Type(-30)) , 0.5);
  TTS_ULP_EQUAL(eve::asind(Type(-1. )) ,  (Type(-90)) , 0.5);
  TTS_ULP_EQUAL(eve::asind(Type( 1. )) ,  (Type(90))  , 0.5);
  TTS_ULP_EQUAL(eve::asind(Type( 0. )) ,  (Type(0))   , 0.5);

  TTS_ULP_EQUAL(eve::asind(eve::Mzero<Type>()), (Type(0)), 0.5);

  TTS_EXPECT( all(is_negative(eve::asind(eve::Mzero<Type>()))) );
  TTS_EXPECT( all(is_positive(eve::asind(Type(0))))            );;
}
