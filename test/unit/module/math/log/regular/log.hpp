//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/log.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::log return type")
{
  TTS_EXPR_IS(eve::log(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::log behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log(eve::inf(eve::as<EVE_TYPE>()))  , eve::inf(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::log(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::log(eve::mone(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::log(EVE_TYPE( 0 ))         , eve::minf(eve::as<EVE_TYPE>()));
  }

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log(eve::mindenormal(eve::as<EVE_TYPE>())), EVE_TYPE(std::log(eve::mindenormal(eve::as<EVE_VALUE>()))));
  }

  TTS_IEEE_EQUAL(eve::log(EVE_TYPE( 1)), EVE_TYPE( 0 )               );
  TTS_IEEE_EQUAL(eve::log(EVE_TYPE( 2)), EVE_TYPE(std::log(EVE_VALUE( 2))) );
  TTS_IEEE_EQUAL(eve::log(EVE_TYPE( 8)), EVE_TYPE(std::log(EVE_VALUE( 8))) );
  TTS_IEEE_EQUAL(eve::log(EVE_TYPE(64)), EVE_TYPE(std::log(EVE_VALUE(64))) );
}
