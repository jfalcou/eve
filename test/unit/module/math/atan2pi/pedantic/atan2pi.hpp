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
#include <eve/function/pedantic.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
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

TTS_CASE_TPL( "Check pedantic(eve::atan2pi) return type", EVE_TYPE)
{
  using eve::pedantic;
  TTS_EXPR_IS(pedantic(eve::atan2pi)(T(0), T(0)), T);
}

TTS_CASE_TPL("Check pedantic(eve::atan2pi) behavior", EVE_TYPE)
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::pedantic;
  using eve::all;

  auto mzero = T(-0.);

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::inf(eve::as<T>());
    auto minf = eve::minf(eve::as<T>());

    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(inf         , (T(1.))  ), (T(0.5))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(inf         , (T(-1.)) ), (T(0.5))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(minf        , (T(1.))  ), (T(-0.5)) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(minf        , (T(-1.)) ), (T(-0.5)) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T( 1.)) , minf        ), (T(1.))   , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(-1.)) , minf        ), (T(-1.))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T( 1.)) , inf         ), (T(0.))   , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(-1.)) , inf         ), mzero        , 0.5);

    TTS_EXPECT( all(is_negative(pedantic(eve::atan2pi)((T(-1.)), inf))) );
    TTS_EXPECT( all(is_positive(pedantic(eve::atan2pi)((T(1.)) , inf))) );

    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(minf, minf      ), (T(-0.75)), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(inf , minf      ), (T(0.75)) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(minf, inf       ), (T(-0.25)), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(inf , inf       ), (T(0.25)) , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(inf , (T(1.))), (T(0.5))  , 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(minf, (T(1.))), (T(-0.5)) , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)(eve::nan(eve::as<T>()), (T(0.)))       , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(0.))      , eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(0.5)) , (T(0.5)) ) , (T(0.25))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(-0.5)), (T(-0.5))) , (T(-0.75)) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(-1.)) , (T(-1.)) ) , (T(-0.75)) , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(1.))  , (T(1.))  ) , (T(0.25))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(0.))  , (T(0.))  ) , (T(0.))    , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)(mzero       , (T(0.))  ) , mzero         , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)(mzero       , mzero       ) , (T(-1.))   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)(mzero       , (T(-1.)) ) , (T(-1.))   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(0.))  , mzero       ) , (T(1.))    , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(0.))  , (T(-1.)) ) , (T(1.))    , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(-1.)) , mzero       ) , (T(-0.5))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(-1.)) , (T(0.))  ) , (T(-0.5))  , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(1.))  , mzero       ) , (T(0.5))   , 0.5);
  TTS_ULP_EQUAL(pedantic(eve::atan2pi)((T(1.))  , (T(0.))  ) , (T(0.5))   , 0.5);
}
