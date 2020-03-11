//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acosh.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::acosh return type")
{
  TTS_EXPR_IS(eve::acosh(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::acosh behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acosh(eve::Nan<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acosh(eve::Inf<EVE_TYPE>()) , eve::Inf<EVE_TYPE>(), 0);
  }

  TTS_ULP_EQUAL(eve::acosh(EVE_TYPE( 0.5))         ,  eve::Nan<EVE_TYPE>()  , 0   );
  TTS_ULP_EQUAL(eve::acosh(EVE_TYPE(-0.5))         ,  eve::Nan<EVE_TYPE>()  , 0   );
  TTS_ULP_EQUAL(eve::acosh(EVE_TYPE( 1. ))         ,  eve::Zero<EVE_TYPE>() , 0   );
  TTS_ULP_EQUAL(eve::acosh(EVE_TYPE( 2. ))         ,  EVE_TYPE(std::acosh(EVE_VALUE(2))), 0.5  );
}
