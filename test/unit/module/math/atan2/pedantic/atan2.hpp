//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan2.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pi.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL( "Check pedantic_(eve::atan2) return type", EVE_TYPE)
{
  using eve::pedantic_;
  TTS_EXPR_IS(pedantic_(eve::atan2)(T(0), T(0)), T);
}

TTS_CASE_TPL("Check pedantic_(eve::atan2) behavior", EVE_TYPE)
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::pedantic_;
  using eve::all;

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Inf<T>()         , T(1.)   ), eve::Pio_2<T>() , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Inf<T>()         , T(-1.)  ), eve::Pio_2<T>() , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Minf<T>()        , T(1.)   ), -eve::Pio_2<T>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Minf<T>()        , T(-1.)  ), -eve::Pio_2<T>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)((T( 1.)) , eve::Minf<T>()       ), eve::Pi<T>()    , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)((T(-1.)) , eve::Minf<T>()       ), -eve::Pi<T>()   , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)((T( 1.)) , eve::Inf<T>()        ), T(0.)         , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)((T(-1.)) , eve::Inf<T>()        ), T(-0.)          , 0.5);

    TTS_EXPECT( all(is_negative(pedantic_(eve::atan2)((T(-1.)), eve::Inf<T>()))) );
    TTS_EXPECT( all(is_positive(pedantic_(eve::atan2)((T(1.)) , eve::Inf<T>()))) );

    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Minf<T>(), eve::Minf<T>()), -3*eve::Pio_4<T>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Inf<T>() , eve::Minf<T>()),  3*eve::Pio_4<T>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Minf<T>(), eve::Inf<T>() ), -eve::Pio_4<T>()  , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Inf<T>() , eve::Inf<T>() ),  eve::Pio_4<T>()  , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Inf<T>() , T(1.)),  eve::Pio_2<T>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Minf<T>(), T(1.)), -eve::Pio_2<T>(), 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Nan<T>(), eve::Nan<T>()) , eve::Nan<T>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)(eve::Nan<T>(), (T(0.)))       , eve::Nan<T>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2)((T(0.))      , eve::Nan<T>()) , eve::Nan<T>(), 0.5);
  }

  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T( 0.5), T( 0.5)) ,  eve::Pio_4<T>()   , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T(-0.5), T(-0.5)) , -3*eve::Pio_4<T>() , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T(-1. ), T(-1. )) , -3*eve::Pio_4<T>() , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T( 1. ), T( 1. )) ,  eve::Pio_4<T>()   , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T( 0. ), T( 0. )) ,  (T(0.))           , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T(-0. ), T( 0. )) ,  T(-0.)            , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T(-0. ), T(-0. )) , -eve::Pi<T>()      , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T(-0. ), T(-1. )) , -eve::Pi<T>()      , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T( 0. ), T(-0. )) ,  eve::Pi<T>()      , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T( 0. ), T(-1. )) ,  eve::Pi<T>()      , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T(-1. ), T(-0. )) , -eve::Pio_2<T>()   , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T(-1. ), T( 0. )) , -eve::Pio_2<T>()   , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T( 1. ), T(-0. )) ,  eve::Pio_2<T>()   , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2)(T( 1. ), T( 0. )) ,  eve::Pio_2<T>()   , 0.5);
}
