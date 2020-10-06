//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/average.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>

TTS_CASE("Check average return type")
{
  TTS_EXPR_IS(eve::average(EVE_TYPE(), EVE_TYPE()), EVE_TYPE );
}

TTS_CASE("Check  eve::average behavior")
{
  TTS_EQUAL(eve::average(EVE_TYPE(1), EVE_TYPE(1) ) , EVE_TYPE(1) );
  TTS_EQUAL(eve::average(EVE_TYPE(0), EVE_TYPE(0) ) , EVE_TYPE(0) );
  TTS_EQUAL(eve::average(EVE_TYPE(1), EVE_TYPE(3) ) , EVE_TYPE(2) );
  TTS_EQUAL(eve::average(eve::valmax(eve::as<EVE_TYPE>()), eve::valmax(eve::as<EVE_TYPE>()) ) , eve::valmax(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::average(eve::valmin(eve::as<EVE_TYPE>()), eve::valmin(eve::as<EVE_TYPE>()) ) , eve::valmin(eve::as<EVE_TYPE>()) );

  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::average(EVE_TYPE(-1), EVE_TYPE(-1)), EVE_TYPE(-1));
  }
}
