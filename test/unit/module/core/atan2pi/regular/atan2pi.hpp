//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

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
  TTS_EXPR_IS(eve::atan2pi(Type(0), Type(0)), (Type));
}

TTS_CASE("Check eve::atan2pi behavior")
{
  using eve::is_negative;
  using eve::is_positive;
  using eve::all;

  auto mzero = eve::Mzero<Type>();

  if constexpr( eve::platform::supports_infinites )
  {
    auto inf  = eve::Inf<Type>();
    auto minf = eve::Minf<Type>();

    TTS_ULP_EQUAL(eve::atan2pi(inf         , (Type(1.))  ), (Type(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf         , (Type(-1.)) ), (Type(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf        , (Type(1.))  ), (Type(-0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf        , (Type(-1.)) ), (Type(-0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((Type( 1.)) , minf        ), (Type(1.))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((Type(-1.)) , minf        ), (Type(-1.)) , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((Type( 1.)) , inf         ), (Type(0.))  , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((Type(-1.)) , inf         ), mzero       , 0.5);

    TTS_EXPECT( all(is_negative(eve::atan2pi((Type(-1.)), inf))) );
    TTS_EXPECT( all(is_positive(eve::atan2pi((Type(1.)) , inf))) );

    TTS_ULP_EQUAL(eve::atan2pi(minf, minf      ),  eve::Nan<Type>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , minf      ),  eve::Nan<Type>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf, inf       ),  eve::Nan<Type>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , inf       ),  eve::Nan<Type>() , 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(inf , (Type(1.))),  (Type(0.5)), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(minf, (Type(1.))), (Type(-0.5)) , 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atan2pi(eve::Nan<Type>(), eve::Nan<Type>()) , eve::Nan<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi(eve::Nan<Type>(), (Type(0.)))       , eve::Nan<Type>(), 0.5);
    TTS_ULP_EQUAL(eve::atan2pi((Type(0.))      , eve::Nan<Type>()) , eve::Nan<Type>(), 0.5);
  }

  TTS_ULP_EQUAL(eve::atan2pi((Type(0.5)) , (Type(0.5)) ) , (Type(0.25)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(-0.5)), (Type(-0.5))) , (Type(-0.75)), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(-1.)) , (Type(-1.)) ) , (Type(-0.75)), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(1.))  , (Type(1.))  ) , (Type(0.25)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , (Type(-1.)) ) , (Type(-1.))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(0.))  , (Type(-1.)) ) , (Type(1.))   , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(-1.)) , mzero       ) , (Type(-0.5)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(-1.)) , (Type(0.))  ) , (Type(-0.5)) , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(1.))  , mzero       ) , (Type(0.5))  , 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(1.))  , (Type(0.))  ) , (Type(0.5))  , 0.5);

  TTS_ULP_EQUAL(eve::atan2pi((Type(0.))  , (Type(0.))  ) ,  eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , (Type(0.))  ) ,  eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi(mzero       , mzero       ) ,  eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::atan2pi((Type(0.))  , mzero       ) ,  eve::Nan<Type>(), 0.5);
}
