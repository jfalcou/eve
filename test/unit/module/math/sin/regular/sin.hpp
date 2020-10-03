//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::sin return type")
{
  TTS_EXPR_IS(eve::sin(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::sin behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sin(eve::nan(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::sin(eve::inf(eve::as<EVE_TYPE>())) , (eve::nan(eve::as<EVE_TYPE>())) );
    TTS_IEEE_EQUAL(eve::sin(eve::minf(eve::as<EVE_TYPE>())), (eve::nan(eve::as<EVE_TYPE>())) );
  }

  TTS_IEEE_EQUAL(eve::sin(EVE_TYPE(0))   , EVE_TYPE(0));
  TTS_IEEE_EQUAL(eve::sin(EVE_TYPE(-0.)) , EVE_TYPE(0));

  TTS_ULP_EQUAL(eve::sin(EVE_TYPE( 1))               , EVE_TYPE(std::sin(EVE_VALUE(1))) , 0.5);
  TTS_ULP_EQUAL(eve::sin(EVE_TYPE(-1))               , EVE_TYPE(std::sin(EVE_VALUE(-1))), 0.5);
  TTS_ULP_EQUAL(eve::sin( eve::pio_4(eve::as<EVE_TYPE>()))    , EVE_TYPE(std::sin(eve::pio_4(eve::as<EVE_VALUE>())))  , 0.5);
  TTS_ULP_EQUAL(eve::sin(-eve::pio_4(eve::as<EVE_TYPE>()))    , EVE_TYPE(std::sin(-eve::pio_4(eve::as<EVE_VALUE>()))) , 0.5);
  TTS_ULP_EQUAL(eve::sin( EVE_TYPE(100000.0))        , EVE_TYPE(std::sin(100000.0)) , 0.5);
  TTS_ULP_EQUAL(eve::sin(-EVE_TYPE(100000.0))        , EVE_TYPE(std::sin(-100000.0)), 0.5);
  TTS_ULP_EQUAL(eve::sin(EVE_TYPE(-100000000.0))     , EVE_TYPE(std::sin(-100000000.0))       , 0.5);
  TTS_ULP_EQUAL(eve::sin(EVE_TYPE(eve::valmax(eve::as<EVE_TYPE>()))) , EVE_TYPE(std::sin(eve::valmax(eve::as<EVE_VALUE>()))) , 0.5);
}
