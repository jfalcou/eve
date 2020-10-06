
//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/manhattan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::manhattan return type")
{
  TTS_EXPR_IS(eve::manhattan(EVE_TYPE(0), EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::manhattan behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::manhattan(eve::nan(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::manhattan(eve::inf(eve::as<EVE_TYPE>()), eve::nan(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()));
  }

  TTS_IEEE_EQUAL(eve::manhattan(eve::valmax(eve::as<EVE_TYPE>()), EVE_TYPE(0))             , eve::valmax(eve::as<EVE_TYPE>()));
  TTS_IEEE_EQUAL(eve::manhattan(EVE_TYPE(0)            , eve::valmax(eve::as<EVE_TYPE>())) , eve::valmax(eve::as<EVE_TYPE>()));

  TTS_IEEE_EQUAL(eve::manhattan(EVE_TYPE(-1), EVE_TYPE(-1)), EVE_TYPE(2));
  TTS_IEEE_EQUAL(eve::manhattan(EVE_TYPE( 1), EVE_TYPE( 1)), EVE_TYPE(2));
  TTS_IEEE_EQUAL(eve::manhattan(EVE_TYPE( 0), EVE_TYPE( 0)), EVE_TYPE(0));
  TTS_ULP_EQUAL(eve::manhattan(eve::sqrt_2(eve::as<EVE_TYPE>()) , eve::sqrt_2(eve::as<EVE_TYPE>())) , EVE_TYPE(2)* eve::sqrt_2(eve::as<EVE_TYPE>()), 0.5);
}

TTS_CASE("Check 3 params eve::manhattan behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::manhattan(eve::nan(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()), 0);
    TTS_ULP_EQUAL(eve::manhattan(eve::inf(eve::as<EVE_TYPE>()), eve::nan(eve::as<EVE_TYPE>()), eve::inf(eve::as<EVE_TYPE>())), eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  TTS_ULP_EQUAL(eve::manhattan(eve::valmax(eve::as<EVE_TYPE>()), EVE_TYPE(0),              EVE_TYPE(0)), eve::valmax(eve::as<EVE_TYPE>()), 0);
  TTS_ULP_EQUAL(eve::manhattan(EVE_TYPE(0)          , (eve::valmax(eve::as<EVE_TYPE>())),  EVE_TYPE(0)), eve::valmax(eve::as<EVE_TYPE>()), 0);

  TTS_ULP_EQUAL(eve::manhattan(EVE_TYPE(-1), EVE_TYPE(-1), EVE_TYPE(-1)), EVE_TYPE(3) , 0);
  TTS_ULP_EQUAL(eve::manhattan(EVE_TYPE( 1), EVE_TYPE( 1), EVE_TYPE(-1)), EVE_TYPE(3) , 0);
  TTS_ULP_EQUAL(eve::manhattan(EVE_TYPE( 0), EVE_TYPE( 0), EVE_TYPE( 0)), EVE_TYPE(0) , 0);
  TTS_ULP_EQUAL(eve::manhattan(EVE_TYPE( 1), EVE_TYPE( 1), EVE_TYPE( 1)), EVE_TYPE(3) , 0);
}
