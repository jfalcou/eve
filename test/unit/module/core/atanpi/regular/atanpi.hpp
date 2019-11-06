//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atanpi.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::atanpi return type")
{
  TTS_EXPR_IS(eve::atanpi(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::atanpi behavior")
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::atanpi(eve::Nan<Type>()), (eve::Nan<Type>()) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::atanpi(eve::Inf<Type>()) , (Type( 0.5)) );
    TTS_IEEE_EQUAL(eve::atanpi(eve::Minf<Type>()), (Type(-0.5)) );
  }

  TTS_ULP_EQUAL(eve::atanpi(Type(0.5))  , (eve::inpi(Type(4.636476090008061e-01))) , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(Type(-0.5)) , (eve::inpi(Type(-4.636476090008061e-01))), 0.5);
  TTS_ULP_EQUAL(eve::atanpi(Type(-1.))  , -Type(0.25)           , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(Type(1.))   ,  Type(0.25)           , 0.5);
  TTS_ULP_EQUAL(eve::atanpi(Type(0.))   , (Type(0))                     , 0.5);

  TTS_EXPECT(all(eve::is_positive(eve::atanpi((Type(0)))))          );
  TTS_EXPECT(all(eve::is_negative(eve::atanpi(eve::Mzero<Type>()))) );
}
