//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asin.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::asin return type")
{
  TTS_EXPR_IS(eve::asin(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::eve::asin behavior")
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asin(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::asin(EVE_TYPE(2))          , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::asin(EVE_TYPE(-2))         , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_ULP_EQUAL(eve::asin(EVE_TYPE( 0.5)) ,  eve::pio_2(eve::as<EVE_TYPE>())/3 , 0.5);
  TTS_ULP_EQUAL(eve::asin(EVE_TYPE(-0.5)) , -eve::pio_2(eve::as<EVE_TYPE>())/3 , 0.5);
  TTS_ULP_EQUAL(eve::asin(EVE_TYPE(-1. )) , -eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::asin(EVE_TYPE( 1. )) ,  eve::pio_2(eve::as<EVE_TYPE>())   , 0.5);
  TTS_ULP_EQUAL(eve::asin(EVE_TYPE( 0. )) ,  EVE_TYPE(0)              , 0.5);

  TTS_ULP_EQUAL(eve::asin(EVE_TYPE(-0.)), EVE_TYPE(0), 0.5);

  TTS_EXPECT( all(is_negative(eve::asin(EVE_TYPE(-0.)))) );
  TTS_EXPECT( all(is_positive(eve::asin(EVE_TYPE(0))))   );
}
