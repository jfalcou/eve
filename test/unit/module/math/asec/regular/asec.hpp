//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asec.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::asec return type")
{
  TTS_EXPR_IS(eve::asec(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::asec behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::asec(eve::inf(eve::as<EVE_TYPE>())),  eve::pio_2(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::asec(eve::minf(eve::as<EVE_TYPE>())), eve::pio_2(eve::as<EVE_TYPE>()) );
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asec(EVE_TYPE(0))   , eve::nan(eve::as<EVE_TYPE>()), 1);
    TTS_ULP_EQUAL(eve::asec(EVE_TYPE(-0.)) , eve::nan(eve::as<EVE_TYPE>()), 1);
    TTS_IEEE_EQUAL(eve::asec(eve::nan(eve::as<EVE_TYPE>()))  , (eve::nan(eve::as<EVE_TYPE>())) );
  }

  TTS_ULP_EQUAL(eve::asec(EVE_TYPE(-2)) , 2*eve::pi(eve::as<EVE_TYPE>())/3 , 1   );
  TTS_ULP_EQUAL(eve::asec(EVE_TYPE( 2)) , eve::pi(eve::as<EVE_TYPE>())/3   , 1   );
  TTS_ULP_EQUAL(eve::asec(EVE_TYPE(-1)) , eve::pi(eve::as<EVE_TYPE>())     , 0.5 );
  TTS_ULP_EQUAL(eve::asec(EVE_TYPE( 1)) , (EVE_TYPE(0))           , 0.5 );
}
