//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan2.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::atan2 return type")
{
  TTS_EXPR_IS(eve::atan2(Type(0), Type(0)), (Type));
}

TTS_CASE("Check eve::atan2 behavior")
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::all;

  auto mzero = eve::Mzero<Type>();

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::Inf<Type>();
    auto minf = eve::Minf<Type>();

    TTS_ULP_EQUAL(eve::atan2(inf         , (Type(1.))  ), eve::Pio_2<Type>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf         , (Type(-1.)) ), eve::Pio_2<Type>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf        , (Type(1.))  ), -eve::Pio_2<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf        , (Type(-1.)) ), -eve::Pio_2<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2((Type( 1.)) , minf        ), eve::Pi<Type>()    , 0.5);
    TTS_ULP_EQUAL(eve::atan2((Type(-1.)) , minf        ), -eve::Pi<Type>()   , 0.5);
    TTS_ULP_EQUAL(eve::atan2((Type( 1.)) , inf         ), (Type(0.))         , 0.5);
    TTS_ULP_EQUAL(eve::atan2((Type(-1.)) , inf         ), mzero              , 0.5);

    TTS_EXPECT( all(is_negative(eve::atan2((Type(-1.)), inf))) );
    TTS_EXPECT( all(is_positive(eve::atan2((Type(1.)) , inf))) );

    TTS_ULP_EQUAL(eve::atan2(minf, minf      ),  eve::Nan<Type>()   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , minf      ),  eve::Nan<Type>()   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf, inf       ),  eve::Nan<Type>()   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , inf       ),  eve::Nan<Type>()   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , (Type(1.))),  eve::Pio_2<Type>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf, (Type(1.))), -eve::Pio_2<Type>() , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan2(eve::Nan<Type>(), eve::Nan<Type>()) , eve::Nan<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::Nan<Type>(), (Type(0.)))       , eve::Nan<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2((Type(0.))      , eve::Nan<Type>()) , eve::Nan<Type>(), 0.5);
  }

  TTS_ULP_EQUAL(eve::atan2((Type(0.5)) , (Type(0.5)) ) ,  eve::Pio_4<Type>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(-0.5)), (Type(-0.5))) , -3*eve::Pio_4<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(-1.)) , (Type(-1.)) ) , -3*eve::Pio_4<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(1.))  , (Type(1.))  ) ,  eve::Pio_4<Type>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , (Type(-1.)) ) , -eve::Pi<Type>()      , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(0.))  , (Type(-1.)) ) ,  eve::Pi<Type>()      , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(-1.)) , mzero       ) , -eve::Pio_2<Type>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(-1.)) , (Type(0.))  ) , -eve::Pio_2<Type>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(1.))  , mzero       ) ,  eve::Pio_2<Type>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(1.))  , (Type(0.))  ) ,  eve::Pio_2<Type>()   , 0.5);

  TTS_ULP_EQUAL(eve::atan2((Type(0.))  , (Type(0.))  ) ,  eve::Nan<Type>()     , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , (Type(0.))  ) ,  eve::Nan<Type>()     , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , mzero       ) ,  eve::Nan<Type>()     , 0.5);
  TTS_ULP_EQUAL(eve::atan2((Type(0.))  , mzero       ) ,  eve::Nan<Type>()     , 0.5);
}
