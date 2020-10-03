//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cscd.hpp>
#include <eve/function/cscpi.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::medium(eve::cscd) return type")
{
  TTS_EXPR_IS(eve::medium(eve::cscd)(EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::medium(eve::cscd) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium(eve::cscd)(eve::nan(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium(eve::cscd)(eve::inf(eve::as<EVE_TYPE>()))  , eve::nan(eve::as<EVE_TYPE>()) );
    TTS_IEEE_EQUAL(eve::medium(eve::cscd)(eve::minf(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()) );
  }

  TTS_IEEE_EQUAL(eve::medium(eve::cscd)(EVE_TYPE( 0 )) , eve::inf(eve::as<EVE_TYPE>()) );
  TTS_IEEE_EQUAL(eve::medium(eve::cscd)(EVE_TYPE(-0.)) , eve::minf(eve::as<EVE_TYPE>()));

  TTS_ULP_EQUAL(eve::medium(eve::cscd)( EVE_TYPE(1)  ) , EVE_TYPE(57.298688498550183476612683735173779889969877177276)   , 5);
  TTS_ULP_EQUAL(eve::medium(eve::cscd)(-EVE_TYPE(1)  ) , EVE_TYPE(-57.298688498550183476612683735173779889969877177276)  , 5);
  TTS_ULP_EQUAL(eve::medium(eve::cscd)( EVE_TYPE(45) ) , EVE_TYPE(1.41421356237309504880168872420969807856967187537694)  , 5);
  TTS_ULP_EQUAL(eve::medium(eve::cscd)(-EVE_TYPE(45) ) , EVE_TYPE(-1.41421356237309504880168872420969807856967187537694) , 5);
  TTS_ULP_EQUAL(eve::medium(eve::cscd)( EVE_TYPE(500)) , EVE_TYPE(1.5557238268604123200563559546372533808211721914623)   , 5);
  TTS_ULP_EQUAL(eve::medium(eve::cscd)(-EVE_TYPE(500)) , EVE_TYPE(-1.5557238268604123200563559546372533808211721914623)  , 5);
}
