//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/mantissa.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>

TTS_CASE("Check eve::mantissa return type")
{
  TTS_EXPR_IS(eve::mantissa(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::mantissa behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::mantissa(eve::inf(eve::as<EVE_TYPE>()))      , eve::inf(eve::as<EVE_TYPE>()) );
    TTS_EQUAL(eve::mantissa(eve::minf(eve::as<EVE_TYPE>()))     , eve::minf(eve::as<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::mantissa(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_EQUAL(eve::mantissa(EVE_TYPE(-1  )), EVE_TYPE(-1    ));
  TTS_EQUAL(eve::mantissa(EVE_TYPE( 1  )), EVE_TYPE( 1    ));
  TTS_EQUAL(eve::mantissa(EVE_TYPE( 0  )), EVE_TYPE( 0    ));
  TTS_EQUAL(eve::mantissa(EVE_TYPE( 2  )), EVE_TYPE( 1    ));
  TTS_EQUAL(eve::mantissa(EVE_TYPE( 1.5)), EVE_TYPE( 1.5  ));
  TTS_EQUAL(eve::mantissa(EVE_TYPE( 2.5)), EVE_TYPE( 1.25 ));
}

