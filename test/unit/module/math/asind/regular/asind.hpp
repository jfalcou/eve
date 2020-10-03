//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asind.hpp>
#include <eve/function/all.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::asind return type")
{
  TTS_EXPR_IS(eve::asind(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::eve::asind behavior")
{
  using eve::all;
  using eve::is_negative;
  using eve::is_positive;

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asind(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::asind(EVE_TYPE(2))          , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::asind(EVE_TYPE(-2))         , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_ULP_EQUAL(eve::asind(EVE_TYPE( 0.5)) , EVE_TYPE(30) , 0.5);
  TTS_ULP_EQUAL(eve::asind(EVE_TYPE(-0.5)) , EVE_TYPE(-30), 0.5);
  TTS_ULP_EQUAL(eve::asind(EVE_TYPE(-1. )) , EVE_TYPE(-90), 0.5);
  TTS_ULP_EQUAL(eve::asind(EVE_TYPE( 1. )) , EVE_TYPE(90) , 0.5);
  TTS_ULP_EQUAL(eve::asind(EVE_TYPE( 0. )) , EVE_TYPE(0)  , 0.5);

  TTS_ULP_EQUAL(eve::asind(EVE_TYPE(-0.)), EVE_TYPE(0), 0.5);

  TTS_EXPECT( all(is_negative(eve::asind(EVE_TYPE(-0.)))) );
  TTS_EXPECT( all(is_positive(eve::asind(EVE_TYPE(0))))   );
}
