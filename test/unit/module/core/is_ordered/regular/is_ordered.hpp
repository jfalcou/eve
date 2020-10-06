//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/is_ordered.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE("Check is_ordered return type")
{
  TTS_EXPR_IS(eve::is_ordered(EVE_TYPE(), EVE_TYPE()), eve::logical<EVE_TYPE>);
}

TTS_CASE("Check eve::is_ordered behavior on arithmetic")
{
  TTS_EQUAL(eve::is_ordered(EVE_TYPE(1), EVE_TYPE(1)), eve::true_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::is_ordered(EVE_TYPE(3), EVE_TYPE(1)), eve::true_(eve::as<EVE_TYPE>()));
  TTS_EQUAL(eve::is_ordered(EVE_TYPE(1), EVE_TYPE(3)), eve::true_(eve::as<EVE_TYPE>()));

  if constexpr(eve::floating_value<EVE_TYPE>)
  {
    TTS_EQUAL(eve::is_ordered(eve::nan(eve::as<EVE_TYPE>()), EVE_TYPE(3)), eve::false_(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::is_ordered(EVE_TYPE(3), eve::nan(eve::as<EVE_TYPE>())), eve::false_(eve::as<EVE_TYPE>()));
    TTS_EQUAL(eve::is_ordered(eve::nan(eve::as<EVE_TYPE>()), eve::nan(eve::as<EVE_TYPE>())), eve::false_(eve::as<EVE_TYPE>()));
  }
}
