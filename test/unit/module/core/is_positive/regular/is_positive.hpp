//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_positive.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check is_positive return type")
{
  TTS_EXPR_IS(eve::is_positive(EVE_TYPE()), eve::logical<EVE_TYPE>);
}

TTS_CASE("Check eve::is_positive behavior")
{
  if constexpr(eve::signed_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::is_positive(EVE_TYPE(-1)), eve::false_(eve::as<EVE_TYPE>()));
  }
  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::is_positive(EVE_TYPE( 0 )), eve::true_(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::is_positive(EVE_TYPE(-0.)), eve::false_(eve::as<EVE_TYPE>()));
  }
  if constexpr(eve::platform::supports_nans && eve::floating_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::is_positive( eve::nan(eve::as<EVE_TYPE>())), eve::false_(eve::as<EVE_TYPE>()) );
    TTS_EQUAL(eve::is_positive(-eve::nan(eve::as<EVE_TYPE>())), eve::true_(eve::as<EVE_TYPE>())  );
  }
  TTS_EQUAL(eve::is_positive(EVE_TYPE(0)), eve::true_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::is_positive(EVE_TYPE(3)), eve::true_(eve::as<EVE_TYPE>()));
}
