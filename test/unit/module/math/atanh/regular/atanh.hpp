//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/atanh.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <cmath>

TTS_CASE("Check eve::atanh return type")
{
  TTS_EXPR_IS(eve::atanh(EVE_TYPE(0)), EVE_TYPE);
}

TTS_CASE("Check eve::atanh behavior")
{

  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::atanh(eve::nan(eve::as<EVE_TYPE>())) , eve::nan(eve::as<EVE_TYPE>()), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::atanh( EVE_TYPE( 1.0)), eve::inf(eve::as<EVE_TYPE>())  , 0);
    TTS_ULP_EQUAL(eve::atanh( EVE_TYPE(-1.0)), eve::minf(eve::as<EVE_TYPE>()) , 0);
  }

  TTS_ULP_EQUAL(eve::atanh(EVE_TYPE( 0.5)) , EVE_TYPE(std::atanh(EVE_VALUE(0.5))) , 0.5 );
  TTS_ULP_EQUAL(eve::atanh(EVE_TYPE(-0.5)) , EVE_TYPE(std::atanh(EVE_VALUE(-0.5))), 0.5 );
  TTS_ULP_EQUAL(eve::atanh(EVE_TYPE( 0. )) , EVE_TYPE(0)                    , 0   );
}
