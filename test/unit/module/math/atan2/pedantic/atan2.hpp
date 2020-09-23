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

TTS_CASE_TPL( "Check pedantic(eve::atan2) return type", EVE_TYPE)
{
  using eve::pedantic;
  TTS_EXPR_IS(pedantic(eve::atan2)(T(0), T(0)), T);
}

TTS_CASE_TPL("Check pedantic(eve::atan2) behavior", EVE_TYPE)
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::pedantic;
  using eve::all;

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>())         , T(1.)   ), eve::pio_2(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>())         , T(-1.)  ), eve::pio_2(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>())        , T(1.)   ), -eve::pio_2(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>())        , T(-1.)  ), -eve::pio_2(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T( 1.)) , eve::minf(eve::as<T>())       ), eve::pi(eve::as<T>())    , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T(-1.)) , eve::minf(eve::as<T>())       ), -eve::pi(eve::as<T>())   , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T( 1.)) , eve::inf(eve::as<T>())        ), T(0.)         , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T(-1.)) , eve::inf(eve::as<T>())        ), T(-0.)          , 0.5);

    TTS_EXPECT( all(is_negative(pedantic(eve::atan2)((T(-1.)), eve::inf(eve::as<T>())))) );
    TTS_EXPECT( all(is_positive(pedantic(eve::atan2)((T(1.)) , eve::inf(eve::as<T>())))) );

    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), -3*eve::pio_4(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>()) , eve::minf(eve::as<T>())),  3*eve::pio_4(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>()), eve::inf(eve::as<T>()) ), -eve::pio_4(eve::as<T>())  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>()) , eve::inf(eve::as<T>()) ),  eve::pio_4(eve::as<T>())  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<T>()) , T(1.)),  eve::pio_2(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<T>()), T(1.)), -eve::pio_2(eve::as<T>()), 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::nan(eve::as<T>()), (T(0.)))       , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((T(0.))      , eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 0.5), T( 0.5)) ,  eve::pio_4(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-0.5), T(-0.5)) , -3*eve::pio_4(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-1. ), T(-1. )) , -3*eve::pio_4(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 1. ), T( 1. )) ,  eve::pio_4(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 0. ), T( 0. )) ,  (T(0.))           , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-0. ), T( 0. )) ,  T(-0.)            , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-0. ), T(-0. )) , -eve::pi(eve::as<T>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-0. ), T(-1. )) , -eve::pi(eve::as<T>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 0. ), T(-0. )) ,  eve::pi(eve::as<T>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 0. ), T(-1. )) ,  eve::pi(eve::as<T>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-1. ), T(-0. )) , -eve::pio_2(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T(-1. ), T( 0. )) , -eve::pio_2(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 1. ), T(-0. )) ,  eve::pio_2(eve::as<T>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(T( 1. ), T( 0. )) ,  eve::pio_2(eve::as<T>())   , 0.5);
}
