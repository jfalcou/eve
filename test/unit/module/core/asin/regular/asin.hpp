//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::asin return type")
{
  TTS_EXPR_IS(eve::asin(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::asin behavior")
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asin(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::asin(Type(2))          , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::asin(Type(-2))         , (eve::Nan<Type>()) );
  }

  TTS_ULP_EQUAL(eve::asin(Type( 0.5)) ,  eve::Pio_2<Type>()/3 , 0.5);
  TTS_ULP_EQUAL(eve::asin(Type(-0.5)) , -eve::Pio_2<Type>()/3 , 0.5);
  TTS_ULP_EQUAL(eve::asin(Type(-1. )) , -eve::Pio_2<Type>()   , 0.5);
  TTS_ULP_EQUAL(eve::asin(Type( 1. )) ,  eve::Pio_2<Type>()   , 0.5);
  TTS_ULP_EQUAL(eve::asin(Type( 0. )) ,  (Type(0))            , 0.5);

  TTS_ULP_EQUAL(eve::asin(eve::Mzero<Type>()), (Type(0)), 0.5);

  TTS_EXPECT( all(is_negative(eve::asin(eve::Mzero<Type>()))) );
  TTS_EXPECT( all(is_positive(eve::asin(Type(0))))            );
}
