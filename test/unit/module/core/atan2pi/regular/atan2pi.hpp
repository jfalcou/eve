//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan2pi.hpp>
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

TTS_CASE("Check eve::atan2pi return type")
{
  TTS_EXPR_IS(eve::atan2pi(EVE_TYPE(0), EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::atan2pi behavior")
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::all;

  auto mzero = eve::Mzero<EVE_TYPE>();

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::Inf<EVE_TYPE>();
    auto minf = eve::Minf<EVE_TYPE>();

    TTS_ULP_EQUAL(eve::atan2pi(inf         , (EVE_TYPE(1.))  ), (EVE_TYPE(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf         , (EVE_TYPE(-1.)) ), (EVE_TYPE(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf        , (EVE_TYPE(1.))  ), (EVE_TYPE(-0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf        , (EVE_TYPE(-1.)) ), (EVE_TYPE(-0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE( 1.)) , minf        ), (EVE_TYPE(1.))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(-1.)) , minf        ), (EVE_TYPE(-1.)) , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE( 1.)) , inf         ), (EVE_TYPE(0.))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(-1.)) , inf         ), mzero       , 0.5);

    TTS_EXPECT( all(is_negative(eve::atan2pi((EVE_TYPE(-1.)), inf))) );
    TTS_EXPECT( all(is_positive(eve::atan2pi((EVE_TYPE(1.)) , inf))) );

    TTS_ULP_EQUAL(eve::atan2pi(minf, minf      ),  eve::Nan<EVE_TYPE>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , minf      ),  eve::Nan<EVE_TYPE>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf, inf       ),  eve::Nan<EVE_TYPE>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , inf       ),  eve::Nan<EVE_TYPE>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , (EVE_TYPE(1.))),  (EVE_TYPE(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf, (EVE_TYPE(1.))), (EVE_TYPE(-0.5)) , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan2pi(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(eve::Nan<EVE_TYPE>(), (EVE_TYPE(0.)))       , eve::Nan<EVE_TYPE>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(0.))      , eve::Nan<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 0.5);
  }

  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(0.5)) , (EVE_TYPE(0.5)) ) , (EVE_TYPE(0.25)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(-0.5)), (EVE_TYPE(-0.5))) , (EVE_TYPE(-0.75)), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(-1.)) , (EVE_TYPE(-1.)) ) , (EVE_TYPE(-0.75)), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(1.))  , (EVE_TYPE(1.))  ) , (EVE_TYPE(0.25)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , (EVE_TYPE(-1.)) ) , (EVE_TYPE(-1.))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(0.))  , (EVE_TYPE(-1.)) ) , (EVE_TYPE(1.))   , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(-1.)) , mzero       ) , (EVE_TYPE(-0.5)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(-1.)) , (EVE_TYPE(0.))  ) , (EVE_TYPE(-0.5)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(1.))  , mzero       ) , (EVE_TYPE(0.5))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(1.))  , (EVE_TYPE(0.))  ) , (EVE_TYPE(0.5))  , 0.5);

  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(0.))  , (EVE_TYPE(0.))  ) ,  eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , (EVE_TYPE(0.))  ) ,  eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , mzero       ) ,  eve::Nan<EVE_TYPE>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((EVE_TYPE(0.))  , mzero       ) ,  eve::Nan<EVE_TYPE>(), 0.5);
}
