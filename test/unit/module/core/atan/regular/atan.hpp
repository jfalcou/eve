//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan.hpp>
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

TTS_CASE("Check eve::atan return type")
{
  TTS_EXPR_IS(eve::atan(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::eve::atan behavior")
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::atan(eve::Nan<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::atan(eve::Inf<EVE_TYPE>()) , (eve::Pio_2<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::atan(eve::Minf<EVE_TYPE>()), (-eve::Pio_2<EVE_TYPE>()));
  }

  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(0.5))  , (EVE_TYPE(4.636476090008061e-01)) , 0.5);
  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(-0.5)) , (EVE_TYPE(-4.636476090008061e-01)), 0.5);
  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(-1.))  , -eve::Pio_4<EVE_TYPE>()           , 0.5);
  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(1.))   ,  eve::Pio_4<EVE_TYPE>()           , 0.5);
  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(0.))   , (EVE_TYPE(0))                     , 0.5);

  TTS_EXPECT(all(eve::is_positive(eve::atan((EVE_TYPE(0)))))          );
  TTS_EXPECT(all(eve::is_negative(eve::atan(eve::Mzero<EVE_TYPE>()))) );
}
