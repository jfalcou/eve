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
#include <eve/function/all.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::atan2d return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::atan2d(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::atan2d behavior", EVE_TYPE)
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::all;

  auto mzero = T(-0.);

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::Inf<T>();
    auto minf = eve::Minf<T>();

    TTS_ULP_EQUAL(eve::atan2d(inf         , (T(1.))  ), (T(90))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2d(inf         , (T(-1.)) ), (T(90))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2d(minf        , (T(1.))  ), -(T(90)) , 0.5);
    TTS_ULP_EQUAL(eve::atan2d(minf        , (T(-1.)) ), -(T(90)) , 0.5);
    TTS_ULP_EQUAL(eve::atan2d((T( 1.)) , minf        ), (T(180))   , 0.5);
    TTS_ULP_EQUAL(eve::atan2d((T(-1.)) , minf        ), (T(-180)) , 0.5);
    TTS_ULP_EQUAL(eve::atan2d((T( 1.)) , inf         ), (T(0.))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2d((T(-1.)) , inf         ), mzero       , 0.5);

    TTS_EXPECT( all(is_negative(eve::atan2d((T(-1.)), inf))) );
    TTS_EXPECT( all(is_positive(eve::atan2d((T(1.)) , inf))) );

    TTS_ULP_EQUAL(eve::atan2d(minf, minf      ), eve::nan(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2d(inf , minf      ), eve::nan(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2d(minf, inf       ), eve::nan(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2d(inf , inf       ), eve::nan(eve::as<T>()) , 0.5);
    TTS_ULP_EQUAL(eve::atan2d(inf , (T(1.))),  (T(90))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2d(minf, (T(1.))), -(T(90))  , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan2d(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2d(eve::nan(eve::as<T>()), (T(0.)))       , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2d((T(0.))      , eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::atan2d((T(0.5)) , (T(0.5)) ) ,  (T(45))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(-0.5)), (T(-0.5))) , -3*(T(45)), 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(-1.)) , (T(-1.)) ) , -3*(T(45)), 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(1.))  , (T(1.))  ) ,  (T(45))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2d(mzero       , (T(-1.)) ) ,  (T(-180)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(0.))  , (T(-1.)) ) ,  (T(180))   , 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(-1.)) , mzero       ) , -(T(90))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(-1.)) , (T(0.))  ) , -(T(90))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(1.))  , mzero       ) ,  (T(90))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(1.))  , (T(0.))  ) ,  (T(90))  , 0.5);

  TTS_ULP_EQUAL(eve::atan2d((T(0.))  , (T(0.))  ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::atan2d(mzero       , (T(0.))  ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::atan2d(mzero       , mzero       ) , eve::nan(eve::as<T>()) , 0.5);
  TTS_ULP_EQUAL(eve::atan2d((T(0.))  , mzero       ) , eve::nan(eve::as<T>()) , 0.5);
}
