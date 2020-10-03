//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/secd.hpp>
#include <eve/function/secpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::secd return type")
{
  TTS_EXPR_IS(eve::secd(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::secd behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::secd(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::secd(eve::inf(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::secd(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::secd(EVE_TYPE( 0  )) , EVE_TYPE(1));
  TTS_IEEE_EQUAL(eve::secd(EVE_TYPE(-0.0)) , EVE_TYPE(1));

  TTS_ULP_EQUAL(eve::secd( EVE_TYPE(  1)  ) , EVE_TYPE(1.00015232804390766542842643421257380147891180422143)  , 3);
  TTS_ULP_EQUAL(eve::secd(-EVE_TYPE(  1)  ) , EVE_TYPE(1.00015232804390766542842643421257380147891180422143)  , 3);
  TTS_ULP_EQUAL(eve::secd( EVE_TYPE( 45.0)) , EVE_TYPE(1.41421356237309504880168872420969807856967187537694)  , 5);
  TTS_ULP_EQUAL(eve::secd(-EVE_TYPE( 45.0)) , EVE_TYPE(1.41421356237309504880168872420969807856967187537694)  , 5);
  TTS_ULP_EQUAL(eve::secd( EVE_TYPE(500.0)) , EVE_TYPE(-1.30540728933227860459313349292274081599849729126374) , 3);
  TTS_ULP_EQUAL(eve::secd(-EVE_TYPE(500.0)) , EVE_TYPE(-1.30540728933227860459313349292274081599849729126374) , 3);
}
