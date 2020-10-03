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

TTS_CASE("Check eve::atan return type")
{
  TTS_EXPR_IS(eve::atan(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::eve::atan behavior")
{
  using eve::all;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::atan(eve::nan(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::atan(eve::inf(eve::as<EVE_TYPE>())) , eve::pio_2(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::atan(eve::minf(eve::as<EVE_TYPE>())), -eve::pio_2(eve::as<EVE_TYPE>()));
  }

  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(0.5))  , EVE_TYPE(4.636476090008061e-01) , 0.5);
  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(-0.5)) , EVE_TYPE(-4.636476090008061e-01), 0.5);
  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(-1.))  , -eve::pio_4(eve::as<EVE_TYPE>())         , 0.5);
  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(1.))   ,  eve::pio_4(eve::as<EVE_TYPE>())         , 0.5);
  TTS_ULP_EQUAL(eve::atan(EVE_TYPE(0.))   , EVE_TYPE(0)                     , 0.5);

  TTS_EXPECT(all(eve::is_positive(eve::atan((EVE_TYPE(0))))) );
  TTS_EXPECT(all(eve::is_negative(eve::atan(EVE_TYPE(-0.)))) );
}
