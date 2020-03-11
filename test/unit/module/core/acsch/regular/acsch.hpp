//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acsch.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::acsch return type")
{
  TTS_EXPR_IS(eve::acsch(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::acsch behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acsch(eve::Nan<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::acsch(eve::Inf<EVE_TYPE>()) , EVE_TYPE(0), 0);
    TTS_ULP_EQUAL(eve::acsch(eve::Minf<EVE_TYPE>()) , EVE_TYPE(-0.0), 0);
    TTS_EXPECT(eve::all(eve::is_negative(eve::acsch(eve::Minf<EVE_TYPE>()))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::acsch(eve::Inf<EVE_TYPE>()))));   
  }

  TTS_ULP_EQUAL(eve::acsch(EVE_TYPE( 0.5)) , EVE_TYPE(std::asinh(EVE_VALUE(2.)))  , 0   );
  TTS_ULP_EQUAL(eve::acsch(EVE_TYPE(-0.5)) , EVE_TYPE(std::asinh(EVE_VALUE(-2.)))  , 0   );
  TTS_ULP_EQUAL(eve::acsch(EVE_TYPE( 1. )) , EVE_TYPE(std::asinh(EVE_VALUE(1.0)))  , 0.5   );
  TTS_ULP_EQUAL(eve::acsch(EVE_TYPE( 2. )) , EVE_TYPE(std::asinh(EVE_VALUE(0.5))), 0.5  );
}
