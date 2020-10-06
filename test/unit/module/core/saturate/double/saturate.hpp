//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/saturate.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <type_traits>

TTS_CASE("Check eve::saturate return type")
{
  TTS_EXPR_IS(eve::saturate(EVE_TYPE(),   eve::as<double>()), EVE_TYPE);
}

TTS_CASE("Check eve::saturate behavior")
{
  TTS_EQUAL(eve::saturate(eve::valmin(eve::as<EVE_TYPE>()), eve::as<double>()), eve::valmin(eve::as<EVE_TYPE>()) );
  TTS_EQUAL(eve::saturate(EVE_TYPE(0)            , eve::as<double>()), EVE_TYPE(0)             );
  TTS_EQUAL(eve::saturate(EVE_TYPE(42.69)        , eve::as<double>()), EVE_TYPE(42.69)         );
  TTS_EQUAL(eve::saturate(eve::valmax(eve::as<EVE_TYPE>()), eve::as<double>()), eve::valmax(eve::as<EVE_TYPE>()) );
}
