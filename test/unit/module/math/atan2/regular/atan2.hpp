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
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE_TPL("Check eve::atan2 return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::atan2(T(0), T(0)), T);
}

TTS_CASE_TPL("Check eve::atan2 behavior", EVE_TYPE)
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::all;

  auto mzero = T(-0.);

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::inf(eve::as<T>());
    auto minf = eve::Minf<T>();

    TTS_ULP_EQUAL(eve::atan2(inf         , (T(1.))  ), eve::Pio_2<T>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf         , (T(-1.)) ), eve::Pio_2<T>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf        , (T(1.))  ), -eve::Pio_2<T>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf        , (T(-1.)) ), -eve::Pio_2<T>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2((T( 1.)) , minf        ), eve::Pi<T>()    , 0.5);
    TTS_ULP_EQUAL(eve::atan2((T(-1.)) , minf        ), -eve::Pi<T>()   , 0.5);
    TTS_ULP_EQUAL(eve::atan2((T( 1.)) , inf         ), (T(0.))         , 0.5);
    TTS_ULP_EQUAL(eve::atan2((T(-1.)) , inf         ), mzero              , 0.5);

    TTS_EXPECT( all(is_negative(eve::atan2((T(-1.)), inf))) );
    TTS_EXPECT( all(is_positive(eve::atan2((T(1.)) , inf))) );

    TTS_ULP_EQUAL(eve::atan2(minf, minf      ),  eve::nan(eve::as<T>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , minf      ),  eve::nan(eve::as<T>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf, inf       ),  eve::nan(eve::as<T>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , inf       ),  eve::nan(eve::as<T>())   , 0.5);
    TTS_ULP_EQUAL(eve::atan2(inf , (T(1.))),  eve::Pio_2<T>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2(minf, (T(1.))), -eve::Pio_2<T>() , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan2(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2(eve::nan(eve::as<T>()), (T(0.)))       , eve::nan(eve::as<T>()), 0.5);
    TTS_ULP_EQUAL(eve::atan2((T(0.))      , eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()), 0.5);
  }

  TTS_ULP_EQUAL(eve::atan2((T(0.5)) , (T(0.5)) ) ,  eve::Pio_4<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(-0.5)), (T(-0.5))) , -3*eve::Pio_4<T>() , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(-1.)) , (T(-1.)) ) , -3*eve::Pio_4<T>() , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(1.))  , (T(1.))  ) ,  eve::Pio_4<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , (T(-1.)) ) , -eve::Pi<T>()      , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(0.))  , (T(-1.)) ) ,  eve::Pi<T>()      , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(-1.)) , mzero       ) , -eve::Pio_2<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(-1.)) , (T(0.))  ) , -eve::Pio_2<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(1.))  , mzero       ) ,  eve::Pio_2<T>()   , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(1.))  , (T(0.))  ) ,  eve::Pio_2<T>()   , 0.5);

  TTS_ULP_EQUAL(eve::atan2((T(0.))  , (T(0.))  ) ,  eve::nan(eve::as<T>())     , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , (T(0.))  ) ,  eve::nan(eve::as<T>())     , 0.5);
  TTS_ULP_EQUAL(eve::atan2(mzero       , mzero       ) ,  eve::nan(eve::as<T>())     , 0.5);
  TTS_ULP_EQUAL(eve::atan2((T(0.))  , mzero       ) ,  eve::nan(eve::as<T>())     , 0.5);
}
