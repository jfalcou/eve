//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atan.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::atan return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::atan(T(0)), T);
}

TTS_CASE_TPL("Check eve::eve::atan behavior", EVE_TYPE)
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::atan(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::atan(eve::inf(eve::as<T>())) , eve::Pio_2<T>() );
    TTS_IEEE_EQUAL(eve::atan(eve::minf(eve::as<T>())), -eve::Pio_2<T>());
  }

  TTS_ULP_EQUAL(eve::atan(T(0.5))  , T(4.636476090008061e-01) , 0.5);
  TTS_ULP_EQUAL(eve::atan(T(-0.5)) , T(-4.636476090008061e-01), 0.5);
  TTS_ULP_EQUAL(eve::atan(T(-1.))  , -eve::Pio_4<T>()         , 0.5);
  TTS_ULP_EQUAL(eve::atan(T(1.))   ,  eve::Pio_4<T>()         , 0.5);
  TTS_ULP_EQUAL(eve::atan(T(0.))   , T(0)                     , 0.5);

  TTS_EXPECT(all(eve::is_positive(eve::atan((T(0))))) );
  TTS_EXPECT(all(eve::is_negative(eve::atan(T(-0.)))) );
}
