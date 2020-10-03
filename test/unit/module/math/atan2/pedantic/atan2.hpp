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
#include <cmath>

TTS_CASE( "Check pedantic(eve::atan2) return type")
{
  using eve::pedantic;
  TTS_EXPR_IS(pedantic(eve::atan2)(EVE_TYPE(0), EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check pedantic(eve::atan2) behavior")
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::pedantic;
  using eve::all;

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<EVE_TYPE>())         , EVE_TYPE(1.)   ), eve::pio_2(eve::as<EVE_TYPE>()) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<EVE_TYPE>())         , EVE_TYPE(-1.)  ), eve::pio_2(eve::as<EVE_TYPE>()) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<EVE_TYPE>())        , EVE_TYPE(1.)   ), -eve::pio_2(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<EVE_TYPE>())        , EVE_TYPE(-1.)  ), -eve::pio_2(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((EVE_TYPE( 1.)) , eve::minf(eve::as<EVE_TYPE>())       ), eve::pi(eve::as<EVE_TYPE>())    , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((EVE_TYPE(-1.)) , eve::minf(eve::as<EVE_TYPE>())       ), -eve::pi(eve::as<EVE_TYPE>())   , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((EVE_TYPE( 1.)) , eve::inf(eve::as<EVE_TYPE>())        ), EVE_TYPE(0.)         , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((EVE_TYPE(-1.)) , eve::inf(eve::as<EVE_TYPE>())        ), EVE_TYPE(-0.)          , 0.5);

    TTS_EXPECT( all(is_negative(pedantic(eve::atan2)((EVE_TYPE(-1.)), eve::inf(eve::as<EVE_TYPE>())))) );
    TTS_EXPECT( all(is_positive(pedantic(eve::atan2)((EVE_TYPE(1.)) , eve::inf(eve::as<EVE_TYPE>())))) );

    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<EVE_TYPE>()), eve::minf(eve::as<EVE_TYPE>())), -3*eve::pio_4(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<EVE_TYPE>()) , eve::minf(eve::as<EVE_TYPE>())),  3*eve::pio_4(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>()) ), -eve::pio_4(eve::as<EVE_TYPE>())  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<EVE_TYPE>()) , eve::inf(eve::as<EVE_TYPE>()) ),  eve::pio_4(eve::as<EVE_TYPE>())  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::inf(eve::as<EVE_TYPE>()) , EVE_TYPE(1.)),  eve::pio_2(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::minf(eve::as<EVE_TYPE>()), EVE_TYPE(1.)), -eve::pio_2(eve::as<EVE_TYPE>()), 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::nan(eve::as<EVE_TYPE>()), eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)(eve::nan(eve::as<EVE_TYPE>()), (EVE_TYPE(0.)))       , eve::nan(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2)((EVE_TYPE(0.))      , eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0.5);
  }

  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE( 0.5), EVE_TYPE( 0.5)) ,  eve::pio_4(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE(-0.5), EVE_TYPE(-0.5)) , -3*eve::pio_4(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE(-1. ), EVE_TYPE(-1. )) , -3*eve::pio_4(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE( 1. ), EVE_TYPE( 1. )) ,  eve::pio_4(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE( 0. ), EVE_TYPE( 0. )) ,  (EVE_TYPE(0.))           , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE(-0. ), EVE_TYPE( 0. )) ,  EVE_TYPE(-0.)            , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE(-0. ), EVE_TYPE(-0. )) , -eve::pi(eve::as<EVE_TYPE>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE(-0. ), EVE_TYPE(-1. )) , -eve::pi(eve::as<EVE_TYPE>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE( 0. ), EVE_TYPE(-0. )) ,  eve::pi(eve::as<EVE_TYPE>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE( 0. ), EVE_TYPE(-1. )) ,  eve::pi(eve::as<EVE_TYPE>())      , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE(-1. ), EVE_TYPE(-0. )) , -eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE(-1. ), EVE_TYPE( 0. )) , -eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE( 1. ), EVE_TYPE(-0. )) ,  eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2)(EVE_TYPE( 1. ), EVE_TYPE( 0. )) ,  eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
}
