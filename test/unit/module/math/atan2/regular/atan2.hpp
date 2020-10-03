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
#include <cmath>

TTS_CASE("Check eve::atan2 return type")
{
  TTS_EXPR_IS(eve::atan2(EVE_TYPE(0), EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::atan2 behavior")
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::all;

  auto mzero = EVE_TYPE(-0.);

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::inf(eve::as<EVE_TYPE>());
    auto minf = eve::minf(eve::as<EVE_TYPE>());

    TTS_ULP_EQUAL(eve::atan2(inf         , (EVE_TYPE(1.))  ), eve::pio_2(eve::as<EVE_TYPE>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf         , (EVE_TYPE(-1.)) ), eve::pio_2(eve::as<EVE_TYPE>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf        , (EVE_TYPE(1.))  ), -eve::pio_2(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf        , (EVE_TYPE(-1.)) ), -eve::pio_2(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2((EVE_TYPE( 1.)) , minf        ), eve::pi(eve::as<EVE_TYPE>())    , 0.5);
    TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(-1.)) , minf        ), -eve::pi(eve::as<EVE_TYPE>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2((EVE_TYPE( 1.)) , inf         ), (EVE_TYPE(0.))         , 0.5);
    TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(-1.)) , inf         ), mzero              , 0.5);

    TTS_EXPECT( all(is_negative(eve::atan2((EVE_TYPE(-1.)), inf))) );
    TTS_EXPECT( all(is_positive(eve::atan2((EVE_TYPE(1.)) , inf))) );

    TTS_ULP_EQUAL(eve::atan2(minf, minf      ),  eve::nan(eve::as<EVE_TYPE>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , minf      ),  eve::nan(eve::as<EVE_TYPE>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf, inf       ),  eve::nan(eve::as<EVE_TYPE>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , inf       ),  eve::nan(eve::as<EVE_TYPE>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , (EVE_TYPE(1.))),  eve::pio_2(eve::as<EVE_TYPE>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf, (EVE_TYPE(1.))), -eve::pio_2(eve::as<EVE_TYPE>()) , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan2(eve::nan(eve::as<EVE_TYPE>()), eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::nan(eve::as<EVE_TYPE>()), (EVE_TYPE(0.)))       , eve::nan(eve::as<EVE_TYPE>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(0.))      , eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(0.5)) , (EVE_TYPE(0.5)) ) ,  eve::pio_4(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(-0.5)), (EVE_TYPE(-0.5))) , -3*eve::pio_4(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(-1.)) , (EVE_TYPE(-1.)) ) , -3*eve::pio_4(eve::as<EVE_TYPE>()) , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(1.))  , (EVE_TYPE(1.))  ) ,  eve::pio_4(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , (EVE_TYPE(-1.)) ) , -eve::pi(eve::as<EVE_TYPE>())      , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(0.))  , (EVE_TYPE(-1.)) ) ,  eve::pi(eve::as<EVE_TYPE>())      , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(-1.)) , mzero       ) , -eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(-1.)) , (EVE_TYPE(0.))  ) , -eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(1.))  , mzero       ) ,  eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(1.))  , (EVE_TYPE(0.))  ) ,  eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);

  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(0.))  , (EVE_TYPE(0.))  ) ,  eve::nan(eve::as<EVE_TYPE>())     , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , (EVE_TYPE(0.))  ) ,  eve::nan(eve::as<EVE_TYPE>())     , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , mzero       ) ,  eve::nan(eve::as<EVE_TYPE>())     , 0.5);
  TTS_ULP_EQUAL(eve::atan2((EVE_TYPE(0.))  , mzero       ) ,  eve::nan(eve::as<EVE_TYPE>())     , 0.5);
}
