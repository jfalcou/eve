//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asinh.hpp>
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

TTS_CASE("Check eve::asinh return type")
{
  TTS_EXPR_IS(eve::asinh(EVE_TYPE(0)), (EVE_TYPE));
}

TTS_CASE("Check eve::asinh behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::asinh(eve::Nan<EVE_TYPE>()) , eve::Nan<EVE_TYPE>(), 0);
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asinh(eve::Inf<EVE_TYPE>()) , eve::Inf<EVE_TYPE>(), 0);
    TTS_ULP_EQUAL(eve::asinh(eve::Minf<EVE_TYPE>()) , eve::Minf<EVE_TYPE>(), 0);    
  }

  TTS_ULP_EQUAL(eve::asinh(EVE_TYPE( 0.5))         ,  EVE_TYPE(std::asinh(EVE_VALUE(0.5))), 0.5  );
  TTS_ULP_EQUAL(eve::asinh(EVE_TYPE(-0.5))         ,  EVE_TYPE(std::asinh(EVE_VALUE(-0.5))), 0.5  );
  TTS_ULP_EQUAL(eve::asinh(EVE_TYPE( 0. ))         ,  eve::Zero<EVE_TYPE>() , 0   );
  TTS_EXPECT(eve::all(eve::is_negative(eve::asinh(eve::Minf<EVE_TYPE>()))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::asinh(eve::Inf<EVE_TYPE>()))));   
  TTS_ULP_EQUAL(eve::asinh(EVE_TYPE( 2. ))         ,  EVE_TYPE(std::asinh(EVE_VALUE(2))), 0.5  );
}
