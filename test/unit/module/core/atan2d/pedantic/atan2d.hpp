//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan2d.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check pedantic_(eve::atan2d) return type")
{
  using eve::pedantic_;
  TTS_EXPR_IS(eve::pedantic_(eve::atan2d)(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check pedantic_(eve::atan2d)  behavior")
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::pedantic_;
  using eve::all;

  auto mzero = eve::Mzero<EVE_TYPE>();

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::Inf<EVE_TYPE>();
    auto minf = eve::Minf<EVE_TYPE>();

    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(inf         , (EVE_TYPE(1.))  ), (EVE_TYPE(90))  , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(inf         , (EVE_TYPE(-1.)) ), (EVE_TYPE(90))  , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(minf        , (EVE_TYPE(1.))  ), -(EVE_TYPE(90)) , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(minf        , (EVE_TYPE(-1.)) ), -(EVE_TYPE(90)) , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE( 1.)) , minf        ), (EVE_TYPE(180)) , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(-1.)) , minf        ), (EVE_TYPE(-180)), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE( 1.)) , inf         ), (EVE_TYPE(0.))  , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(-1.)) , inf         ), mzero       , 0.5);

    TTS_EXPECT( all(is_negative(pedantic_(eve::atan2d)((EVE_TYPE(-1.)), inf))) );
    TTS_EXPECT( all(is_positive(pedantic_(eve::atan2d)((EVE_TYPE(1.)) , inf))) );

    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(minf, minf      ), -3*(EVE_TYPE(45)), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(inf , minf      ),  3*(EVE_TYPE(45)), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(minf, inf       ), -(EVE_TYPE(45))  , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(inf , inf       ),  (EVE_TYPE(45))  , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(inf , (EVE_TYPE(1.))),  (EVE_TYPE(90))  , 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(minf, (EVE_TYPE(1.))), -(EVE_TYPE(90))  , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)(eve::Nan<EVE_TYPE>(), (EVE_TYPE(0.)))       , eve::Nan<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(0.))      , eve::Nan<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 0.5);
  }

  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(0.5)) , (EVE_TYPE(0.5)) ) ,  (EVE_TYPE(45))  , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(-0.5)), (EVE_TYPE(-0.5))) , -3*(EVE_TYPE(45)), 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(-1.)) , (EVE_TYPE(-1.)) ) , -3*(EVE_TYPE(45)), 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(1.))  , (EVE_TYPE(1.))  ) ,  (EVE_TYPE(45))  , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(0.))  , (EVE_TYPE(0.))  ) ,  (EVE_TYPE(0.))  , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)(mzero       , (EVE_TYPE(0.))  ) ,  mzero       , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)(mzero       , mzero       ) ,  (EVE_TYPE(-180)) , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)(mzero       , (EVE_TYPE(-1.)) ) ,  (EVE_TYPE(-180)) , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(0.))  , mzero       ) ,  (EVE_TYPE(180))   , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(0.))  , (EVE_TYPE(-1.)) ) ,  (EVE_TYPE(180))   , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(-1.)) , mzero       ) , -(EVE_TYPE(90))  , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(-1.)) , (EVE_TYPE(0.))  ) , -(EVE_TYPE(90))  , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(1.))  , mzero       ) ,  (EVE_TYPE(90))  , 0.5);
  TTS_ULP_EQUAL(pedantic_(eve::atan2d)((EVE_TYPE(1.))  , (EVE_TYPE(0.))  ) ,  (EVE_TYPE(90))  , 0.5);
}
